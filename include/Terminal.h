#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdbool.h>

void initTerminal(void);
void restoreTerminal(void);
void clearScreen(void);
void hideCursor(void);
void showCursor(void);
void moveCursor(int row, int col);
bool keyAvailable(void);
void sleepMs(int milliseconds);

#endif

