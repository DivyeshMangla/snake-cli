#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdbool.h>

typedef enum {
    COLOR_RESET = 0,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_WHITE,
    COLOR_BRIGHT_GREEN,
    COLOR_BRIGHT_YELLOW,
    COLOR_BRIGHT_RED,
    COLOR_GRAY
} TermColor;

void initTerminal(void);
void restoreTerminal(void);
void clearScreen(void);
void hideCursor(void);
void showCursor(void);
void moveCursor(int row, int col);
void setColor(TermColor color);
void resetColor(void);
bool keyAvailable(void);
void sleepMs(int milliseconds);

#endif