#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point *body;
    int length;
    int capacity;
    Direction direction;
    Direction nextDirection;
} Snake;

Snake *createSnake(int startX, int startY, int initialCapacity);
void freeSnake(Snake *snake);

void setSnakeDirection(Snake *snake, Direction dir);
void moveSnake(Snake *snake);
void growSnake(Snake *snake);
Point getSnakeHead(const Snake *snake);
bool snakeCollidesWithSelf(const Snake *snake);
bool snakeOccupies(const Snake *snake, int x, int y);

#endif

