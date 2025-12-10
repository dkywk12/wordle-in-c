#include<stdio.h>
#include "tools.h"

#ifdef _WIN32
    #include<windows.h>
    #include<conio.h>
#endif

Color white = {255, 255, 255};
Color black = {0, 0, 0};

Color boardColor = {10, 10, 10};
Color textColor = {255, 255, 255};
Color correctColor = {22, 166, 32};
Color incorrectColor = {128, 128, 128};
Color partialColor = {242, 230, 44};

//In Windows we need to enable ANSI escape codes to
//interact with the terminal more easily
#ifdef _WIN32
    DWORD oldConsoleMode, newConsoleMode;
    //Enable ANSI escape codes on Windows and disable ECHO
    void setTerminalMode(){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        //Get the current console mode
        GetConsoleMode(hConsole, &oldConsoleMode);
        newConsoleMode = oldConsoleMode;
        //Disable echo in terminal
        newConsoleMode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
        //Enable Virtual Terminal Processing 
        //This is so that ANSI escape codes work on Windows
        //terminal
        newConsoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hConsole, newConsoleMode);
    }
    //Reset original console mode
    void resetTerminalMode(){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleMode(hConsole, oldConsoleMode);
    }
#endif

//Go to position in screen
void gotoxy(int x, int y){
    printf("%c[%d;%df", 0x1B, x, y);
}

//Set RGB color
//Foreground color
void setColorForeground(Color *c){
    printf("\033[38;2;%d;%d;%dm", c->r, c->g, c->b);  
}
//Background color
void setColorBackground(Color *c){
    printf("\033[48;2;%d;%d;%dm", c->r, c->g, c->b);  
}

//Reset colors to default
void resetColor(){
    printf("\033[0m");
}

//Clears all characters in screen
void clearScreen(){
    resetColor();
    #ifdef _WIN32
        system("cls");
    #endif
}

//Change font style
void setBold(){
    printf("\033[1m");
}
void resetStyle(){
    printf("\033[22m");
}

//Waits some time in miliseconds
void wait(double t){
    #ifdef _WIN32
        Sleep(t);
    #endif
}

void clearBuffer(){
    char key;
    while(kbhit()){
        key = getch();
    }
}

void hideCursor(){
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = FALSE; //Set cursor visibility to false
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    #endif
}

void showCursor(){
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = TRUE; //Set cursor visibility to true
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    #endif
}
