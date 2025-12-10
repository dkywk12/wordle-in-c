//This header has all the functions needed to interact
//with the terminal
#ifndef _TOOLS_H_
#define _TOOLS_H_

typedef struct{
    int r, g, b;
}Color;

extern Color white;
extern Color black;

extern Color boardColor;
extern Color textColor;
extern Color correctColor;
extern Color incorrectColor;
extern Color partialColor;

void setTerminalMode();
void resetTerminalMode();

//Declare functions kbhit and getch if we are
//not in Windows
#ifndef _WIN32
    int kbhit();
    int getch();
#endif

void gotoxy(int, int);
void setColorForeground(Color*);
void setColorBackground(Color*);
void resetColor();
void clearScreen();
void setBold();
void resetStyle();

void wait(double);
void clearBuffer();

void hideCursor();
void showCursor();

#endif