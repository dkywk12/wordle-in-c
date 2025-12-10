#include "tools.h"
#include "setup.h"

#ifdef _WIN32
    #include<conio.h>
    #include<windows.h>
#endif

void setGame(){
    setTerminalMode();
    #ifdef _WIN32
        SetConsoleCtrlHandler(NULL, TRUE); //Disable signal handling in Windows,
        //this is so that Ctrl + C doesn't work and the terminal can be properly
        //restored
    #endif
    clearScreen();
}

void quitGame(){
    gotoxy(1, 1);
    clearScreen();
    resetColor();
    resetTerminalMode();
    #ifdef _WIN32
        SetConsoleCtrlHandler(NULL, FALSE); //Restore signal handling in Windows
    #endif
    showCursor();
    exit(EXIT_SUCCESS); //Terminate program
}