#include <fstream>
#include "tools.h"
#include "config.h"
#include "setup.h"
#include "interface.h"

#ifdef _WIN32
    #include<conio.h>
#endif

const Screen screen = {{1, 1}, SCREEN_C / BLOCK_W, SCREEN_R / BLOCK_H};
const Board board = {
    {((SCREEN_R / BLOCK_H) - BOARD_H) / 2, ((SCREEN_C / BLOCK_W) - BOARD_W) / 2},
        BOARD_W, BOARD_H}; 

const Coordinate startMenuPosition = {(SCREEN_R - 4) / 2, (SCREEN_C - 34) / 2};
const Coordinate inputPosition = {1, 1};

void startMenu(){
    hideCursor();
    setColorBackground(&black);

    for(int i = 0; i < screen.height; i++){
        for(int j = 0; j < screen.width; j++){
            gotoxy(screen.position.x + BLOCK_H * i, screen.position.y + BLOCK_W * j);
            printf(BLOCK);
        }
    }

    std::ifstream titleFile;
    titleFile.open("assets\\title.txt", std::ifstream::in);

    setColorForeground(&white);
    gotoxy(startMenuPosition.x, startMenuPosition.y);
    char ch;
    int lineNumber = 0;
    while(titleFile.good()){
        titleFile.get(ch);
        if(ch == '\n'){
            lineNumber++;
            gotoxy(startMenuPosition.x + lineNumber, startMenuPosition.y);
        }
        else{
            printf("%c", ch);
        }
    }
    titleFile.close();
    fflush(stdout);

    char key;
    while(1){ 
        if(kbhit()){
            key = getch();
            if(key == keyEnter){
                break;
            }
            if(key == keyQuit){
                quitGame();
            }
        }
    }
}

void drawScreen(){
    hideCursor();
    setColorBackground(&black);
    for(int i = 0; i < screen.height; i++){
        for(int j = 0; j < screen.width; j++){
            gotoxy(screen.position.x + BLOCK_H * i, screen.position.y + BLOCK_W * j);
            printf(BLOCK);
        }
    }
    
    for(int i = 0; i < board.height; i++){
        for(int j = 0; j < board.width; j++){
            setColorBackground(&boardColor);
            gotoxy(screen.position.x + BLOCK_H * (board.position.x + i),
                screen.position.y + BLOCK_W * (board.position.y + j));
            printf(BLOCK);
        }
    }
}