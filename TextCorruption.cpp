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
#include "GameLogic.h"

#include <iostream>

unsigned int getCountOfCorruptCharacters(const char* text, const double corruptionRate) {

    const unsigned int letterCount = getCountOfLettersInText(text);

    const unsigned int countOfCorrupted = (letterCount * corruptionRate) + 0.5;

    if (countOfCorrupted <= 0) {

        std::cout << "Error! There aren't enough compatible characters in the text to be corrupted.";
        return 0;
    }

    return countOfCorrupted;
}

char corruptCharLetter(const char initial) {

    if (!isLetter(initial)) return 0;

    const int randomBitPosition = std::rand() % 6;

    const int toggleBitMask = 1 << randomBitPosition;

    const char corrupted = initial ^ toggleBitMask;

    return corrupted;
}

bool generateCorruptedCharacters(char* corruptChars, const unsigned int countOfCorrupted, const char* text, const unsigned int textLength) {

    if (corruptChars == nullptr) return false;
    if (text == nullptr) return false;
    if (countOfCorrupted == 0) return false;
    if (textLength == 0) return false;
    if (textLength < countOfCorrupted) return false;

    int count = 0;
    while (count < countOfCorrupted) {

        const unsigned int randomIndex = std::rand() % textLength;

        if (!isLetter(text[randomIndex])) continue;
        if (corruptChars[randomIndex] != 0) continue;

        corruptChars[randomIndex] = text[randomIndex];

        count++;
    }

    return true;
}

bool checkIfThereAreEnoughLettersToCorruptInText(const char* text, const double corruptionRate) {

    if (text == nullptr) return false;
    if (text[0] == 0) return false;

    const unsigned int corruptedCharsCount = getCountOfCorruptCharacters(text, corruptionRate);
    const unsigned int totalLettersCount = getCountOfLettersInText(text);

    return totalLettersCount >= corruptedCharsCount;
}

bool corruptText(char* text, const char* corruptChars, const unsigned int textLength) {

    if (text == nullptr) return false;
    if (corruptChars == nullptr) return false;
    if (textLength == 0) return false;

    for (int i = 0; i < textLength; i++) {

        if (corruptChars[i] != 0) text[i] = corruptCharLetter(text[i]);
    }

    return true;
}

bool generateCharVariationsFromCorruptedChar(char* charVariations, const char corruptedChar) {

    if (charVariations == nullptr) return false;

    constexpr unsigned short countOfCharVariations = 6;

    for (int i = 0; i < countOfCharVariations; i++) {

        // generating mask for the bit on i-th position
        const int toggleBitMask = 1 << i;

        // flipping the bit on i-th position
        const char charVariation = corruptedChar ^ toggleBitMask;

        charVariations[i] = charVariation;
    }

    return true;
}

bool characterIsCorrupted(const char* text, const char* corruptChars, unsigned int charIndex) {

    if (text == nullptr) return false;
    if (corruptChars == nullptr) return false;

    if (corruptChars[charIndex] == 0) return false;
    return true;
}