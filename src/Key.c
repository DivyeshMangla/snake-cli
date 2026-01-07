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
// POSIX (Linux / macOS)
#include <unistd.h>
#include <termios.h>

static void set_raw_mode(int enable) {
    static struct termios old;
    struct termios new;

    if (enable) {
        tcgetattr(STDIN_FILENO, &old);
        new = old;
        new.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
    }
}

Key read_key(void) {
    Key k = { KEY_NONE, 0 };
    char c;

    set_raw_mode(1);
    read(STDIN_FILENO, &c, 1);

    if (c == 27) { // ESC
        char seq[2];
        read(STDIN_FILENO, &seq[0], 1);
        read(STDIN_FILENO, &seq[1], 1);

        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': k.type = KEY_UP;    break;
                case 'B': k.type = KEY_DOWN;  break;
                case 'C': k.type = KEY_RIGHT; break;
                case 'D': k.type = KEY_LEFT;  break;
            }
        }
    } else {
        k.type = KEY_CHAR;
        k.ch = c;
    }

    set_raw_mode(0);
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