#include "tools.h"
#include "setup.h"

#ifdef _WIN32
    #include<conio.h>
    #include<windows.h>
#endif

void setGame(){
    setTerminalMode();
    #ifdef _WIN32
        SetConsoleCtrlHandler(NULL, TRUE);
    #endif
    clearScreen();
}

void quitGame(){
    gotoxy(1, 1);
    clearScreen();
    resetColor();
    resetTerminalMode();
    #ifdef _WIN32
        SetConsoleCtrlHandler(NULL, FALSE);
    #endif
    showCursor();
    exit(EXIT_SUCCESS);
}