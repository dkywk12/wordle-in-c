#include<string>
#include<cctype>
#include "tools.h"
#include "config.h"
#include "guesser.h"

#ifdef _WIN32
    #include<conio.h>
    #include<windows.h>
#endif

std::string inputHandler(){
    std::string userInput = "";
    char key;

    setColorBackground(&boardColor);
    setColorForeground(&textColor);
    setBold();
    while(1){
        if(kbhit()){
            key = getch();
            if(key == keyQuit){
                break;
            }
            else if(key == '\b'){
                if(!userInput.empty()){
                    printf("\b");
                    printf(BLOCK);
                    printf("\b");
                    userInput.pop_back();
                }
            }
            else if(std::isalpha(key)){
                if(userInput.size() < 5){
                    key = std::toupper(key);
                    userInput.push_back(key);
                    printf("%c", key);
                }
            }
        }
    }
    return userInput;
}