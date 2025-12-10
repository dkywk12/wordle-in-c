#include<string>
#include<cctype>
#include "src/tools.h"
#include "src/setup.h"
#include "src/interface.h"
#include "src/guesser.h"

#ifdef _WIN32
    #include<conio.h> //getch and kbhit in Windows
    #include<windows.h>
#endif

int main(){
    setGame();

    startMenu();
    drawScreen();
    
    inputHandler();

    quitGame();
}