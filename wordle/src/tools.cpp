#include<stdio.h>
#include "tools.h"

#ifdef _WIN32
    #include<windows.h>
    #include<conio.h>
#endif

Color white = {255, 255, 255};
Color black = {0, 0, 0};

Color boardColor = {20, 20, 20};
Color textColor = {255, 255, 255};
Color correctColor = {22, 166, 32};
Color incorrectColor = {120, 124, 127};
Color partialColor = {255, 215, 39};


#ifdef _WIN32
    DWORD oldConsoleMode, newConsoleMode;
    void setTerminalMode(){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleMode(hConsole, &oldConsoleMode);
        newConsoleMode = oldConsoleMode;
        newConsoleMode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
        newConsoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hConsole, newConsoleMode);
    }
    void resetTerminalMode(){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleMode(hConsole, oldConsoleMode);
    }
#endif

void gotoxy(int x, int y){
    printf("%c[%d;%df", 0x1B, x, y);
}

void setColorForeground(Color *c){
    printf("\033[38;2;%d;%d;%dm", c->r, c->g, c->b);  
}

void setColorBackground(Color *c){
    printf("\033[48;2;%d;%d;%dm", c->r, c->g, c->b);  
}

void resetColor(){
    printf("\033[0m");
}

void clearScreen(){
    resetColor();
    #ifdef _WIN32
        system("cls");
    #endif
}

void setBold(){
    printf("\033[1m");
}
void resetStyle(){
    printf("\033[22m");
}

void hideCursor(){
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    #endif
}

void showCursor(){
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = TRUE;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    #endif
}
