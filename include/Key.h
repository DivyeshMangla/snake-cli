#ifndef KEY_H
#define KEY_H

typedef enum {
    KEY_NONE = 0,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_CHAR
} KeyType;

typedef struct {
    KeyType type;
    char ch;        // valid only if type == KEY_CHAR (0 by default)
} Key;

Key readKey(void);

const char *keyTypeToStr(KeyType type);

#endif
