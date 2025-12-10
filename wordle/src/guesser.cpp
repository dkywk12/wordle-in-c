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
#include "setup.h"

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

std::string bottomMessage[2] = {
    "    You guessed the word!   ",
    "Nice try. The word was XXXXX"
};

void writeBottomMessage(int index){
    gotoxy(screen.position.x + BLOCK_H * (board.position.x + board.height) + 1,
        screen.position.y + BLOCK_W * board.position.y - 10);
    setColorBackground(&black);
    setColorForeground(&white);
    resetStyle();
    for(int i = 0; i < bottomMessage[index].size(); i++){
        printf("%c", bottomMessage[index][i]);
    }
    if(index == 1){
        for(int i = 0; i < 5; i++){
            printf("\b");
        }
        for(int i = 0; i < 5; i++){
            printf("%c", secretWord[i]);
        }
    }
}

void finishRound(int result){
    hideCursor();
    writeBottomMessage(result);
    gotoxy(screen.position.x + BLOCK_H * (board.position.x + board.height) + 2,
        screen.position.y + BLOCK_W * board.position.y - 7);
    printf("Wanna play again? [y/n]");
    char key;
    while(1){ 
        if(kbhit()){
            key = getch();
            if(key == 'y'){
                return;
            }
            else if(key == keyQuit || key == 'n'){
                quitGame();
            }
        }
    }
}

int wordsCounter;

void selectRandomWord(){
    int index = rd(0, wordBank.size() - 1);
    secretWord = wordBank[index];

    wordsCounter = 0;
}

std::string topMessage[3] = {
    "                  ",
    "Not enough letters",
    " Not in word list "
};

void writeTopMessage(int index){
    gotoxy(screen.position.x + BLOCK_H * board.position.x - 2,
        screen.position.y + BLOCK_W * board.position.y - 5);
    setColorBackground(&black);
    setColorForeground(&white);
    resetStyle();
    for(int i = 0; i < topMessage[index].size(); i++){
        printf("%c", topMessage[index][i]);
    }
}

enum colorCode{
    correct,
    incorrect,
    partial,
};

bool printGuessWord(std::string word){
    std::multiset<char> secretWordLetters;
    for(int i = 0; i < 5; i++){
        secretWordLetters.insert(secretWord[i]);
    }
    colorCode lcc[5];
    int correctLetters = 0;
    for(int i = 0; i < 5; i++){
        if(word[i] == secretWord[i]){
            lcc[i] = correct;
            secretWordLetters.erase(secretWordLetters.find(word[i]));
            correctLetters++;
        }
    }

    for(int i = 0; i < 5; i++){
        if(word[i] != secretWord[i]){
            if(secretWordLetters.count(word[i])){
                lcc[i] = partial;
                secretWordLetters.erase(secretWordLetters.find(word[i]));
            }
            else{
                lcc[i] = incorrect;
            }
        }
    }

    setColorForeground(&textColor);
    for(int i = 0; i < 5; i++){
        switch(lcc[i]){
        case correct:
            setColorBackground(&correctColor);
            break;
        case incorrect:
            setColorBackground(&incorrectColor);
            break;
        case partial:
            setColorBackground(&partialColor);
            break;
        }
        printf("%c", word[i]);
    }

    if(correctLetters == 5){
        return true;
    }
    return false;
}

void startGuessing(){
    std::string userInput = "";
    char key;

    setColorBackground(&boardColor);
    setColorForeground(&textColor);
    setBold();
    gotoxy(screen.position.x +
        BLOCK_H * (board.position.x + inputPosition.x + wordsCounter),
        screen.position.y +
        BLOCK_W * (board.position.y + inputPosition.y));
    showCursor();
    while(1){
        if(kbhit()){
            key = getch();
            if(key == keyQuit){
                quitGame();
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
                    writeTopMessage(0);
                    gotoxy(screen.position.x +
                        BLOCK_H * (board.position.x + inputPosition.x + wordsCounter),
                        screen.position.y + BLOCK_W * (board.position.y + inputPosition.y));
                    setColorBackground(&boardColor);
                    setColorForeground(&textColor);
                    setBold();
                    if(wordBankSet.count(userInput)){
                        int result = printGuessWord(userInput);
                        if(result){
                            finishRound(0);
                            return;
                        }
                        else{
                            wordsCounter++;
                            if(wordsCounter < 6){
                                userInput.clear();
                                gotoxy(screen.position.x +
                                    BLOCK_H * (board.position.x + inputPosition.x + wordsCounter),
                                    screen.position.y +
                                    BLOCK_W * (board.position.y + inputPosition.y));
                                setColorBackground(&boardColor);
                            }
                            else{
                                finishRound(1);
                                return;
                            }
                        }
                    }
                    else{  
                        writeTopMessage(2);
                        gotoxy(screen.position.x +
                            BLOCK_H * (board.position.x + inputPosition.x + wordsCounter),
                            screen.position.y +
                            BLOCK_W * (board.position.y + inputPosition.y + userInput.size()));
                        setColorBackground(&boardColor);
                        setColorForeground(&textColor);
                        setBold();
                    }
                }
                else{
                    writeTopMessage(1);
                    gotoxy(screen.position.x +
                        BLOCK_H * (board.position.x + inputPosition.x + wordsCounter),
                        screen.position.y +
                        BLOCK_W * (board.position.y + inputPosition.y + userInput.size()));
                    setColorBackground(&boardColor);
                    setColorForeground(&textColor);
                    setBold();
                }
            }
        }
    }
}