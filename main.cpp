#include <iostream>
#include <cstdlib>
#include <ctime>

#include <windows.h>

#include "FileHandling.h"
#include "StringUtils.h"
#include "TextCorruption.h"
#include "GameLogic.h"


void TESTING_printStringFromSize(char* array, unsigned int size);

int main() {
    std::srand(std::time(0));

    // HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // DWORD dwMode = 0;
    // GetConsoleMode(hOut, &dwMode);
    // dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    // SetConsoleMode(hOut, dwMode);

    //TODO input the file name and corruption rate
    char filePath[] = "temp.txt";
    double corruptionRate = 0.8;

    //TODO textLength is going to be a dynamic variable, since we will learn the path runtime
    unsigned int textLength = getTextLengthFromFile(filePath);

    // we have to add one more element for the '\0'
    char* text = new char[textLength + 1];
    char* corruptChars = new char[textLength];

    extractTextFromFile(filePath, text);

    int wordCount = getWordCountOfText(text);
    std::cout << "Word count: " << wordCount << std::endl;

    fillCharArrayWithDefaultValues(corruptChars, textLength, 0);

    unsigned int countOfCorrupted = (textLength * corruptionRate);

    if (!checkIfThereAreEnoughLettersToCorruptInText(text, textLength, corruptionRate)) {

        std::cout << "Error! There aren't enough compatible characters in the text to be corrupted.";
        return -1;
    }

    generateCorruptedCharacters(corruptChars, countOfCorrupted, text, textLength);

    corruptText(text, corruptChars, textLength);

    unsigned int userMistakes = 0;

    // testing

    //TODO optimize function
    //TODO once t is corrupted to u it cannot be fixed back to t
    play(text, corruptChars, countOfCorrupted, wordCount, userMistakes);

    // testing


    // freeing memory in order of allocating it
    delete[] text;
    delete[] corruptChars;

}

void TESTING_printStringFromSize(char* array, unsigned int size) {

    if (array == nullptr) return;

    for (int i = 0; i < size; i++) {

        if (array[i] == 0) std::cout << " ";
        else std::cout << array[i];
    }

    std::cout << std::endl;
}