#include<string>
#include<cctype>
#include<fstream>
#include<vector>
#include<set>
#include<random>
#include "tools.h"
#include "config.h"
#include "guesser.h"
#include "interface.h"

#ifdef _WIN32
    #include<conio.h>
    #include<windows.h>
#endif

struct RandomGen{
    std::mt19937 randomEngine;
    RandomGen(){
        std::random_device rdev;
        std::vector<uint32_t> seedSeq;
        for(int i = 0; i < 4; i++){
            seedSeq.push_back(rdev());
        }
        std::seed_seq seq(seedSeq.begin(), seedSeq.end());
        randomEngine.seed(seq);
    }
    int operator ()(int l, int r){
        std::uniform_int_distribution<int> udist(l, r);
        return udist(randomEngine);
    }
};
RandomGen rd;

std::vector<std::string> wordBank;
std::set<std::string> wordBankSet;
std::string secretWord;

void initializer(){
    std::ifstream wordsFile;
    wordsFile.open("data\\words.txt", std::ifstream::in);

    std::string s;
    while(wordsFile.good()){
        wordsFile>> s;
        wordBank.push_back(s);
        wordBankSet.insert(s);
    }
    wordsFile.close();
}

void selectRandomWord(){
    int index = rd(0, wordBank.size() - 1);
    secretWord = wordBank[index];
}

std::string userWords[5];

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
            else if(key == keyEnter){
                if(userInput.size() == 5){
                    gotoxy(screen.position.x + BLOCK_H * board.position.x - 2,
                        screen.position.y + BLOCK_W * board.position.y - 5);
                    setColorBackground(&black);
                    printf("                  ");
                    gotoxy(screen.position.x + BLOCK_H * (board.position.x + inputPosition.x),
                        screen.position.y + BLOCK_W * (board.position.y + inputPosition.y));
                    setColorBackground(&boardColor);
                    setColorForeground(&textColor);
                    setBold();
                    if(wordBankSet.count(userInput)){
                        setColorBackground(&correctColor);
                        for(int i = 0; i < 5; i++){
                            printf("%c", userInput[i]);
                        }
                    }
                    else{  
                        gotoxy(screen.position.x + BLOCK_H * board.position.x - 2,
                            screen.position.y + BLOCK_W * board.position.y - 5);
                        setColorBackground(&black);
                        setColorForeground(&white);
                        resetStyle();
                        printf(" Not in word list ");
                        gotoxy(screen.position.x + BLOCK_H * (board.position.x + inputPosition.x),
                            screen.position.y +
                            BLOCK_W * (board.position.y + inputPosition.y + userInput.size()));
                        setColorBackground(&boardColor);
                        setColorForeground(&textColor);
                        setBold();
                    }
                    setColorBackground(&boardColor);
                }
                else{
                    gotoxy(screen.position.x + BLOCK_H * board.position.x - 2,
                        screen.position.y + BLOCK_W * board.position.y - 5);
                    setColorBackground(&black);
                    setColorForeground(&white);
                    resetStyle();
                    printf("Not enough letters");
                    gotoxy(screen.position.x + BLOCK_H * (board.position.x + inputPosition.x),
                        screen.position.y +
                        BLOCK_W * (board.position.y + inputPosition.y + userInput.size()));
                    setColorBackground(&boardColor);
                    setColorForeground(&textColor);
                    setBold();
                }
            }
        }
    }
    return userInput;
}