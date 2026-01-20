#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "Snake.h"
#include "Food.h"

typedef enum {
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_GAME_OVER,
    STATE_QUIT
} GameState;

typedef struct {
    Snake *snake;
    Food food;
    int width;
    int height;
    int score;
    GameState state;
    unsigned long tickCount;
} Game;

Game *createGame(int width, int height);
void freeGame(Game *game);

void handleGameInput(Game *game);
void updateGame(Game *game);
void renderGame(const Game *game);
void runGame(Game *game);

#endif

