#include <stdbool.h>
#include <stdio.h>

#include "Key.h"

static bool running = true;

void handleInput(void) {
    const Key key = readKey();

    printf("Pressed Key = %s\n", keyTypeToStr(key.type));

    if (key.type == KEY_CHAR && key.ch == 'q') {
        running = false;   // quit on 'q'
    }
}

void update(void) {
    // do nothing atm
}

void render(void) {
    // do nothing atm
}

int main(void) {
    while (running) {
        handleInput();
        update();
        render();
    }

    return 0;
}