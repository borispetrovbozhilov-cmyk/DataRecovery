#include <iostream>
#include <cstdlib>
#include <ctime>

#include "FileHandling.h"
#include "StringUtils.h"
#include "TextCorruption.h"

int main() {
    std::srand(std::time(0));


    unsigned int textLength = getTextLengthFromFile("testInput.txt");

    char* text = new char[textLength];

    extractTextFromFile("testInput.txt", text, textLength);

    //testing
    std::cout << getCountOfCorruptCharacters(0.49999, textLength) << std::endl;

    std::cout << text << std::endl;

    //testing


    delete[] text;
}