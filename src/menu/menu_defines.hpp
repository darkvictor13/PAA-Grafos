#ifndef MENU
#define MENU

#include <iostream>
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

#define ESC 27

#endif
