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
    char ch;        // valid only if type == KEY_CHAR
} Key;

Key read_key(void);

const char *key_type_to_string(KeyType type);

#endif
