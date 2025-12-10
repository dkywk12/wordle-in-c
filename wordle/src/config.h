#ifndef _CONFIG_H_
#define _CONFIG_H_

#define SCREEN_C 40 
#define SCREEN_R 16

#ifdef _WIN32
	#define keyEnter '\r'
#endif

#define keyQuit ','

#define BLOCK_W 1
#define BLOCK_H 1

#define BLOCK " "

// This is in 'BLOCK' dimensions

#define BOARD_W 7
#define BOARD_H 8

typedef struct{
    int x, y;
}Coordinate;

int equalCoordinates(const Coordinate*, const Coordinate*);

#endif