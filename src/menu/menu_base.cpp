#include "menu_base.hpp"

#ifdef __gnu_linux__

/**
 * @brief
 * 
 * @return char 
 * @pre Nenhuma
 * @post Nenhuma
 */
char MenuBase::getChar() {
    char character = 0;
    struct termios old = {0};
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&character,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    return character;
}

#else

/**
 * @brief
 * 
 * @return char 
 * @pre Nenhuma
 * @post Nenhuma
 */
char MenuBase::getChar() {
    DWORD mode, cc;
    HANDLE h = GetStdHandle( STD_INPUT_HANDLE );
    if (h == NULL)
        return 0; // console not found
    GetConsoleMode( h, &mode );
    SetConsoleMode( h, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT) );
    TCHAR c = 0;
    ReadConsole( h, &c, 1, &cc, NULL );
    SetConsoleMode( h, mode );
    return c;
}

#endif //__gnu_linux__

MenuReturn MenuBase::loop() {
    char input_char;
    while(input_char != ESC) {
        system(CLEAR);
        input_char = getChar();
    }
}
