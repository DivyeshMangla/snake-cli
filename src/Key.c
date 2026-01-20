#include "key.h"

#ifdef _WIN32
#include <conio.h>

Key readKey(void) {
    Key k = { KEY_NONE, 0 };
    int ch = _getch();

    if (ch == 0 || ch == 224) {
        ch = _getch();
        switch (ch) {
            case 72: k.type = KEY_UP;    break;
            case 80: k.type = KEY_DOWN;  break;
            case 75: k.type = KEY_LEFT;  break;
            case 77: k.type = KEY_RIGHT; break;
            default: k.type = KEY_NONE;  break;
        }
    } else {
        k.type = KEY_CHAR;
        k.ch = (char)ch;
    }

    return k;
}

#else
#include <unistd.h>
#include <termios.h>

static void setRawMode(int enable) {
    static struct termios original;
    struct termios raw;

    if (enable) {
        tcgetattr(STDIN_FILENO, &original);
        raw = original;
        raw.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &original);
    }
}

Key readKey(void) {
    Key k = { KEY_NONE, 0 };
    char c;

    setRawMode(1);
    read(STDIN_FILENO, &c, 1);

    if (c == 27) {
        char seq[2];
        read(STDIN_FILENO, &seq[0], 1);
        read(STDIN_FILENO, &seq[1], 1);

        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': k.type = KEY_UP;    break;
                case 'B': k.type = KEY_DOWN;  break;
                case 'C': k.type = KEY_RIGHT; break;
                case 'D': k.type = KEY_LEFT;  break;
                default: break;
            }
        }
    } else {
        k.type = KEY_CHAR;
        k.ch = c;
    }

    setRawMode(0);
    return k;
}
#endif

const char *keyTypeToStr(const KeyType type) {
    switch (type) {
        case KEY_UP:    return "KEY_UP";
        case KEY_DOWN:  return "KEY_DOWN";
        case KEY_LEFT:  return "KEY_LEFT";
        case KEY_RIGHT: return "KEY_RIGHT";
        case KEY_CHAR:  return "KEY_CHAR";
        default:        return "KEY_NONE";
    }
}