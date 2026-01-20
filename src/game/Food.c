#include "game/Food.h"
#include <stdlib.h>
#include <time.h>

static bool seeded = false;

Food spawnFood(int width, int height, const Snake *snake) {
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = true;
    }

    Food food;
    int attempts = 0;
    int maxAttempts = width * height;

    do {
        food.x = rand() % width;
        food.y = rand() % height;
        attempts++;
    } while (snakeOccupies(snake, food.x, food.y) && attempts < maxAttempts);

    return food;
}

