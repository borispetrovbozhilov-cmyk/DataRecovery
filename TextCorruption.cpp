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

unsigned int getWordCountOfText(const char* text) {

    if (text == nullptr) return 0;
    if (text[0] == '\0') return 0;

    int currentIndex = 0;
    int wordCount = 0;

    while (true) {

        if (isLetter(text[currentIndex])) {

            wordCount++;

            while (isLetter(text[currentIndex++]) && text[currentIndex] != '\0');
            currentIndex--;
        }

        currentIndex++;
        if (text[currentIndex] == '\0') break;
    }

    return wordCount;
}

unsigned int getCountOfLettersInText(const char* text) {

    if (text == nullptr) return 0;
    if (text[0] == '\0') return 0;

    unsigned int currentIndex = 0;
    unsigned int letterCount = 0;

    while (text[currentIndex] != '\0') {

        if (isLetter(text[currentIndex])) letterCount++;
        currentIndex++;
    }

    return letterCount;
}

bool checkIfThereAreEnoughLettersToCorruptInText(const char* text, unsigned int textLength, double corruptionRate) {

    if (text == nullptr) return false;
    if (textLength <= 0) return false;

    unsigned int corruptedCharsCount = getCountOfCorruptCharacters(corruptionRate, textLength);
    unsigned int totalLettersCount = getCountOfLettersInText(text);

    return totalLettersCount >= corruptedCharsCount;
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

bool generateCharVariationsFromCorruptedChar(char* charVariations, char corruptedChar) {

    if (charVariations == nullptr) return false;

    unsigned short countOfCharVariations = 6;

    for (int i = 0; i < countOfCharVariations; i++) {

        // generating mask for the bit on i-th position
        int toggleBitMask = 1 << i;

        // flipping the bit on i-th position
        char charVariation = corruptedChar ^ toggleBitMask;

        charVariations[i] = charVariation;
    }

    return true;
}