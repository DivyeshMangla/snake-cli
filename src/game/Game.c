#include "game/Game.h"
#include "Key.h"
#include "Terminal.h"
#include <stdio.h>
#include <stdlib.h>

#define BASE_TICK_MS 200
#define TICK_REDUCTION_PER_SPEED 15
#define BORDER_CHAR '#'
#define SNAKE_HEAD '@'
#define SNAKE_BODY 'o'
#define FOOD_CHAR '*'
#define EMPTY_CHAR ' '

Game *createGame(int width, int height) {
    Game *game = malloc(sizeof(Game));
    if (!game) return NULL;

    game->width = width;
    game->height = height;
    game->score = 0;
    game->speed = SPEED_DEFAULT;
    game->state = STATE_RUNNING;
    game->tickCount = 0;

    int startX = width / 2;
    int startY = height / 2;
    game->snake = createSnake(startX, startY, width * height);
    if (!game->snake) {
        free(game);
        return NULL;
    }

    game->food = spawnFood(width, height, game->snake);

    return game;
}

void freeGame(Game *game) {
    if (game) {
        freeSnake(game->snake);
        free(game);
    }
}

void handleGameInput(Game *game) {
    if (!keyAvailable()) return;

    Key key = readKey();

    if (game->state == STATE_GAME_OVER) {
        if (key.type == KEY_CHAR && (key.ch == 'r' || key.ch == 'R')) {
            int w = game->width;
            int h = game->height;
            freeSnake(game->snake);
            game->snake = createSnake(w / 2, h / 2, w * h);
            game->food = spawnFood(w, h, game->snake);
            game->score = 0;
            game->tickCount = 0;
            game->state = STATE_RUNNING;
        } else if (key.type == KEY_CHAR && (key.ch == 'q' || key.ch == 'Q')) {
            game->state = STATE_QUIT;
        }
        return;
    }

    if (key.type == KEY_CHAR) {
        switch (key.ch) {
            case 'q':
            case 'Q':
                game->state = STATE_QUIT;
                break;
            case 'p':
            case 'P':
                game->state = (game->state == STATE_PAUSED) ? STATE_RUNNING : STATE_PAUSED;
                break;
            case 'w':
            case 'W':
                setSnakeDirection(game->snake, DIR_UP);
                break;
            case 's':
            case 'S':
                setSnakeDirection(game->snake, DIR_DOWN);
                break;
            case 'a':
            case 'A':
                setSnakeDirection(game->snake, DIR_LEFT);
                break;
            case 'd':
            case 'D':
                setSnakeDirection(game->snake, DIR_RIGHT);
                break;
            case '+':
            case '=':
                if (game->speed < SPEED_MAX) game->speed++;
                break;
            case '-':
            case '_':
                if (game->speed > SPEED_MIN) game->speed--;
                break;
        }
    } else {
        switch (key.type) {
            case KEY_UP:    setSnakeDirection(game->snake, DIR_UP);    break;
            case KEY_DOWN:  setSnakeDirection(game->snake, DIR_DOWN);  break;
            case KEY_LEFT:  setSnakeDirection(game->snake, DIR_LEFT);  break;
            case KEY_RIGHT: setSnakeDirection(game->snake, DIR_RIGHT); break;
            default: break;
        }
    }
}

void updateGame(Game *game) {
    if (game->state != STATE_RUNNING) return;

    moveSnake(game->snake);

    Point head = getSnakeHead(game->snake);

    if (head.x < 0 || head.x >= game->width ||
        head.y < 0 || head.y >= game->height) {
        game->state = STATE_GAME_OVER;
        return;
    }

    if (snakeCollidesWithSelf(game->snake)) {
        game->state = STATE_GAME_OVER;
        return;
    }

    if (head.x == game->food.x && head.y == game->food.y) {
        game->score += 10;
        growSnake(game->snake);
        game->food = spawnFood(game->width, game->height, game->snake);
    }

    game->tickCount++;
}

static void renderBorder(const Game *game) {
    int totalWidth = game->width + 2;

    setColor(COLOR_CYAN);
    moveCursor(0, 0);
    for (int i = 0; i < totalWidth; i++) {
        putchar(BORDER_CHAR);
    }

    for (int y = 0; y < game->height; y++) {
        moveCursor(y + 1, 0);
        putchar(BORDER_CHAR);
        moveCursor(y + 1, game->width + 1);
        putchar(BORDER_CHAR);
    }

    moveCursor(game->height + 1, 0);
    for (int i = 0; i < totalWidth; i++) {
        putchar(BORDER_CHAR);
    }
    resetColor();
}

static void renderPlayfield(const Game *game) {
    for (int y = 0; y < game->height; y++) {
        moveCursor(y + 1, 1);
        for (int x = 0; x < game->width; x++) {
            putchar(EMPTY_CHAR);
        }
    }
}

static void renderSnake(const Game *game) {
    for (int i = 0; i < game->snake->length; i++) {
        Point p = game->snake->body[i];
        moveCursor(p.y + 1, p.x + 1);
        setColor(i == 0 ? COLOR_BRIGHT_GREEN : COLOR_GREEN);
        putchar(i == 0 ? SNAKE_HEAD : SNAKE_BODY);
    }
    resetColor();
}

static void renderFood(const Game *game) {
    moveCursor(game->food.y + 1, game->food.x + 1);
    setColor(COLOR_BRIGHT_RED);
    putchar(FOOD_CHAR);
    resetColor();
}

static void renderStatus(const Game *game) {
    moveCursor(game->height + 2, 0);
    setColor(COLOR_BRIGHT_YELLOW);
    printf("Score: %-6d", game->score);
    setColor(COLOR_CYAN);
    printf(" Speed: %d/%d  ", game->speed, SPEED_MAX);
    resetColor();

    moveCursor(game->height + 3, 0);
    switch (game->state) {
        case STATE_PAUSED:
            setColor(COLOR_YELLOW);
            printf("[PAUSED] Press P to resume                    ");
            break;
        case STATE_GAME_OVER:
            setColor(COLOR_BRIGHT_RED);
            printf("[GAME OVER] Press R to restart, Q to quit     ");
            break;
        default:
            setColor(COLOR_GRAY);
            printf("WASD/Arrows: move | +/-: speed | P: pause | Q: quit");
            break;
    }
    resetColor();
}

void renderGame(const Game *game) {
    renderBorder(game);
    renderPlayfield(game);
    renderSnake(game);
    renderFood(game);
    renderStatus(game);
    fflush(stdout);
}

static int getTickDelay(int speed) {
    return BASE_TICK_MS - (speed * TICK_REDUCTION_PER_SPEED);
}

void runGame(Game *game) {
    initTerminal();
    clearScreen();

    while (game->state != STATE_QUIT) {
        handleGameInput(game);
        updateGame(game);
        renderGame(game);
        sleepMs(getTickDelay(game->speed));
    }

    restoreTerminal();
}