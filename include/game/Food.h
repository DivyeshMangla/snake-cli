#ifndef FOOD_H
#define FOOD_H

#include "Snake.h"

typedef struct {
    int x;
    int y;
} Food;

Food spawnFood(int width, int height, const Snake *snake);

#endif

