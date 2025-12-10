#ifndef _UI_H_
#define _UI_H_

#include "config.h"

typedef struct{
    Coordinate position; 
    int width;
    int height;
}Screen;

extern const Screen screen;

typedef struct{
	Coordinate position;
    int width;
    int height;
}Board;

extern const Board board;

extern const Coordinate startMenuPosition;
extern const Coordinate inputPosition;

void startMenu();
void drawScreen();

typedef enum{
	correctInput,
    wrongInput
}InputResult;

#endif