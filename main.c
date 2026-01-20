#include "game/Game.h"
#include <stdlib.h>

#define GAME_WIDTH 30
#define GAME_HEIGHT 15

int main(void) {
    Game *game = createGame(GAME_WIDTH, GAME_HEIGHT);
    if (!game) {
        return EXIT_FAILURE;
    }

    runGame(game);
    freeGame(game);

    return EXIT_SUCCESS;
}
