#include<string>
#include<cctype>
#include "config.h"
#include "guesser.h"

#ifdef _WIN32
    #include<conio.h>
    #include<windows.h>
#endif

std::string inputHandler(){
    std::string userInput = "";
    char key;
    while(1){
        if(kbhit()){ //Wait til a key is pressed
            key = getch();
            if(key == keyQuit){
                break;
            }
            if(std::isalpha(key)){
                key = std::toupper(key);
                userInput.push_back(key);
                printf("%c", key);
            }
        }
    }
    return userInput;
}