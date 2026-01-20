#include "game/Snake.h"
#include <stdlib.h>
#include <string.h>

Snake *createSnake(int startX, int startY, int initialCapacity) {
    Snake *snake = malloc(sizeof(Snake));
    if (!snake) return NULL;

    snake->body = malloc(sizeof(Point) * initialCapacity);
    if (!snake->body) {
        free(snake);
        return NULL;
    }

    snake->capacity = initialCapacity;
    snake->length = 3;
    snake->direction = DIR_RIGHT;
    snake->nextDirection = DIR_RIGHT;

    for (int i = 0; i < snake->length; i++) {
        snake->body[i].x = startX - i;
        snake->body[i].y = startY;
    }

    return snake;
}

void freeSnake(Snake *snake) {
    if (snake) {
        free(snake->body);
        free(snake);
    }
}

void setSnakeDirection(Snake *snake, Direction dir) {
    Direction current = snake->direction;

    bool oppositeDir = (dir == DIR_UP && current == DIR_DOWN) ||
                       (dir == DIR_DOWN && current == DIR_UP) ||
                       (dir == DIR_LEFT && current == DIR_RIGHT) ||
                       (dir == DIR_RIGHT && current == DIR_LEFT);

    if (!oppositeDir) {
        snake->nextDirection = dir;
    }
}

void moveSnake(Snake *snake) {
    snake->direction = snake->nextDirection;

    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }

    switch (snake->direction) {
        case DIR_UP:    snake->body[0].y--; break;
        case DIR_DOWN:  snake->body[0].y++; break;
        case DIR_LEFT:  snake->body[0].x--; break;
        case DIR_RIGHT: snake->body[0].x++; break;
    }
}

void growSnake(Snake *snake) {
    if (snake->length >= snake->capacity) {
        int newCapacity = snake->capacity * 2;
        Point *newBody = realloc(snake->body, sizeof(Point) * newCapacity);
        if (!newBody) return;
        snake->body = newBody;
        snake->capacity = newCapacity;
    }

    snake->body[snake->length] = snake->body[snake->length - 1];
    snake->length++;
}

Point getSnakeHead(const Snake *snake) {
    return snake->body[0];
}

bool snakeCollidesWithSelf(const Snake *snake) {
    Point head = snake->body[0];
    for (int i = 1; i < snake->length; i++) {
        if (snake->body[i].x == head.x && snake->body[i].y == head.y) {
            return true;
        }
    }
    return false;
}

bool snakeOccupies(const Snake *snake, int x, int y) {
    for (int i = 0; i < snake->length; i++) {
        if (snake->body[i].x == x && snake->body[i].y == y) {
            return true;
        }
    }
    return false;
}

