#include <stdbool.h>
#include <stdio.h>

#include "Key.h"

static bool running = true;

void handle_input(void) {
    const Key key = read_key();

    printf("Pressed Key = %s\n", key_type_to_string(key.type));

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
        handle_input();
        update();
        render();
    }

    return 0;
}