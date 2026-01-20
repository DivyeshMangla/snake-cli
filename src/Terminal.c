#include "Terminal.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>

static HANDLE hConsole;
static DWORD originalMode;

void initTerminal(void) {
    hConsole = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hConsole, &originalMode);
    SetConsoleMode(hConsole, originalMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD outMode;
    GetConsoleMode(hOut, &outMode);
    SetConsoleMode(hOut, outMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    hideCursor();
}

void restoreTerminal(void) {
    SetConsoleMode(hConsole, originalMode);
    showCursor();
    clearScreen();
}

void clearScreen(void) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = { 0, 0 };

    if (GetConsoleScreenBufferInfo(hOut, &csbi)) {
        cellCount = csbi.dwSize.X * csbi.dwSize.Y;
        FillConsoleOutputCharacter(hOut, ' ', cellCount, homeCoords, &count);
        FillConsoleOutputAttribute(hOut, csbi.wAttributes, cellCount, homeCoords, &count);
        SetConsoleCursorPosition(hOut, homeCoords);
    }
}

void hideCursor(void) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

void showCursor(void) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

void moveCursor(int row, int col) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)col, (SHORT)row };
    SetConsoleCursorPosition(hOut, pos);
}

bool keyAvailable(void) {
    return _kbhit() != 0;
}

void sleepMs(int milliseconds) {
    Sleep(milliseconds);
}

#else
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <sys/ioctl.h>

static struct termios originalTermios;
static bool terminalModified = false;

void initTerminal(void) {
    tcgetattr(STDIN_FILENO, &originalTermios);
    struct termios raw = originalTermios;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    terminalModified = true;
    hideCursor();
}

void restoreTerminal(void) {
    if (terminalModified) {
        tcsetattr(STDIN_FILENO, TCSANOW, &originalTermios);
        terminalModified = false;
    }
    showCursor();
    clearScreen();
}

void clearScreen(void) {
    printf("\033[2J\033[H");
    fflush(stdout);
}

void hideCursor(void) {
    printf("\033[?25l");
    fflush(stdout);
}

void showCursor(void) {
    printf("\033[?25h");
    fflush(stdout);
}

void moveCursor(int row, int col) {
    printf("\033[%d;%dH", row + 1, col + 1);
    fflush(stdout);
}

bool keyAvailable(void) {
    struct timeval tv = { 0, 0 };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

void sleepMs(int milliseconds) {
    usleep(milliseconds * 1000);
}

#endif

static const char *getColorCode(TermColor color) {
    switch (color) {
        case COLOR_RED:          return "\033[31m";
        case COLOR_GREEN:        return "\033[32m";
        case COLOR_YELLOW:       return "\033[33m";
        case COLOR_BLUE:         return "\033[34m";
        case COLOR_MAGENTA:      return "\033[35m";
        case COLOR_CYAN:         return "\033[36m";
        case COLOR_WHITE:        return "\033[37m";
        case COLOR_BRIGHT_GREEN: return "\033[92m";
        case COLOR_BRIGHT_YELLOW:return "\033[93m";
        case COLOR_BRIGHT_RED:   return "\033[91m";
        case COLOR_GRAY:         return "\033[90m";
        default:                 return "\033[0m";
    }
}

void setColor(TermColor color) {
    printf("%s", getColorCode(color));
}

void resetColor(void) {
    printf("\033[0m");
}