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
    double corruptionRate = 0.5;

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

    // testing
    printCorruptedText(text, corruptChars);
    TESTING_printStringFromSize(corruptChars, textLength);

    unsigned int* wordPosition = new unsigned int;

    promptAskUserToChooseWord(wordPosition, wordCount);

    unsigned int wordIndex;
    getIndexOfWordOnGivenPosition(text, corruptChars, *wordPosition, wordIndex);

    unsigned int wordLength;
    getLengthOfWordStartingOnGivenIndex(text, corruptChars, wordIndex, wordLength);

    promptPrintSelectedWord(text, corruptChars, wordIndex, wordLength);

    unsigned int* charPosition = new unsigned int;
    promptAskForCharacterPosition(text, wordLength, charPosition);


    // testing




    // freeing memory in order of allocating it
    delete[] text;
    delete[] corruptChars;
    delete wordPosition;
    delete charPosition;
}

void TESTING_printStringFromSize(char* array, unsigned int size) {

    if (array == nullptr) return;

    for (int i = 0; i < size; i++) {

        if (array[i] == 0) std::cout << " ";
        else std::cout << array[i];
    }

    std::cout << std::endl;
}