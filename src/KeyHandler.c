#include "KeyHandler.h"

void handleKey(const Key key) {
    if (key.type == KEY_CHAR && key.ch == 'Q') {
        handleQuitKey();
    }
}

void handleQuitKey() {
    // Implement quit logic here
}

void handleUpwardArrow() {}
void handleDownwardArrow() {}
void handleLeftArrow() {}
void handleRightArrow() {}