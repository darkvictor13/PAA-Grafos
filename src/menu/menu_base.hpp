#ifndef MENU_BASE
#define MENU_BASE

#include <stdlib.h> 

#ifdef __gnu_linux__

#include <termios.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>

#define ENTER 10
#define CLEAR "clear"

#else

#include <conio.h>
#include <wchar.h>
#include <windows.h>

#define ENTER 13
#define CLEAR "cls"

#endif //__gnu_linux__

#define UP 'w'
#define DOWN 's'
#define ESC 27

enum MenuMove {
    MOVE_BACKWARD,
    MOVE_FOWARD
};

enum MenuReturn {
    STAY,
    GO_BACK
};

class MenuBase {
    protected:
        char getChar();

    public:
        MenuReturn loop();

};

#endif
