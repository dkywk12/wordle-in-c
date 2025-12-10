#include<string>
#include<cctype>
#include "src/setup.h"
#include "src/interface.h"
#include "src/guesser.h"

#ifdef _WIN32
    #include<conio.h>
    #include<windows.h>
#endif

int main(){
    setGame();

    //startMenu();
    initializer();
    while(1){
        drawScreen();
        selectRandomWord();
        startGuessing();
    }
    
    quitGame();
}