#ifndef KEYHANDLER_H
#define KEYHANDLER_H
#include "Key.h"

void handleKey(Key key);

// Special func keys
void handleQuitKey();

// Arrow keys
void handleUpwardArrow();
void handleDownwardArrow();
void handleLeftArrow();
void handleRightArrow();

#endif //KEYHANDLER_H
