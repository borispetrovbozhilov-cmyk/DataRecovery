/**
*
* Solution to course project # 12
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Boris Bozhilov
* @idnumber 1МІ0600658
* @compiler GCC
*
* This source file holds the logic for the corruption and colouring of the text
*
*/

#include "TextCorruption.h"

#include <iostream>

#include "FileHandling.h"

unsigned int getCountOfCorruptCharacters(double corruptionRate, unsigned int textLength) {

    if (corruptionRate < 0 || corruptionRate > 1) return 0;

    return corruptionRate * textLength + 0.5;
}

bool isLetter(char target) {

    return (target >= 'a' && target <= 'z') || (target >= 'A' && target <= 'Z');
}

char corruptCharLetter(char initial) {

    if (!isLetter(initial)) return 0;

    int randomBitPosition = std::rand() % 6;

    int toggleBitMask = 1 << randomBitPosition;

    char corrupted = initial ^ toggleBitMask;

    return corrupted;
}

// TODO This algorithm is slow.
// TODO Its complexity grows approximate to the number of non letter characters and the corruption rate.
bool generateCorruptedCharacters(char* corruptChars, unsigned int countOfCorrupted, const char* text, unsigned int textLength) {

    if (corruptChars == nullptr) return false;
    if (text == nullptr) return false;
    if (countOfCorrupted == 0) return false;
    if (textLength == 0) return false;
    if (textLength < countOfCorrupted) return false;

    int count = 0;
    while (count < countOfCorrupted) {

        unsigned int randomIndex = std::rand() % textLength;

        if (!isLetter(text[randomIndex])) continue;
        if (corruptChars[randomIndex] != 0) continue;

        corruptChars[randomIndex] = text[randomIndex];

        count++;
    }

    return true;
}

bool checkIfNumberIsInArray(const unsigned int* array, unsigned int size, unsigned int target) {

    if (array == nullptr) return false;
    if (size == 0) return false;

    for (int i = 0; i < size; i++) {

        if (array[i] == target) return true;
    }

    return false;
}

bool corruptText(char* text, char* corruptChars, unsigned int textLength) {

    if (text == nullptr) return false;
    if (corruptChars == nullptr) return false;
    if (textLength == 0) return false;

    for (int i = 0; i < textLength; i++) {

        if (corruptChars[i] != 0) text[i] = corruptCharLetter(text[i]);
    }

    return true;
}

bool printCorruptedText(char* text, char* corruptChars) {

    if (text == nullptr) return false;
    if (corruptChars == nullptr) return false;

    for (int i = 0; text[i] != '\0'; i++) {

        if (corruptChars[i] == '\0') {

            std::cout << text[i];
            continue;
        }

        if (text[i] == corruptChars[i]) std::cout << "\033[32m" << text[i] << "\033[0m";
        if (text[i] != corruptChars[i]) std::cout << "\033[31m" << text[i] << "\033[0m";
    }

    std::cout << std::endl;

    return true;
}