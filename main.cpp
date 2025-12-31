#include <iostream>
#include <cstdlib>
#include <ctime>

#include <windows.h>

#include "FileHandling.h"
#include "StringUtils.h"
#include "TextCorruption.h"


void TESTING_printStringFromSize(char* array, unsigned int size);

int main() {
    std::srand(std::time(0));

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    //TODO textLength is going to be a dynamic variable, since we will learn the path runtime
    unsigned int textLength = getTextLengthFromFile("temp.txt");

    std::cout << textLength << std::endl;

    // we have to add one more element for the '\0'
    char* text = new char[textLength + 1];
    char* corruptChars = new char[textLength];

    extractTextFromFile("temp.txt", text);
    fillCharArrayWithDefaultValues(corruptChars, textLength, 0);

    //testing

    generateCorruptedCharacters(corruptChars, (textLength / 2), text, textLength);

    corruptText(text, corruptChars, textLength);

    printCorruptedText(text, corruptChars);
    TESTING_printStringFromSize(corruptChars, textLength);

    // testing


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