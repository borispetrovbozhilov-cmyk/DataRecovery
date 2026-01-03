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
* This source file holds the logic for the gameplay of the game
*
*/

#include <iostream>
#include "GameLogic.h"
#include "TextCorruption.h"

bool printCorruptedText(const char* text, const char* corruptChars) {

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

void promptAskUserToChooseWord(unsigned int* &wordPosition, unsigned int wordCount) {

    std::cout << "Enter the number of the word you wish to inspect: ";

    unsigned int tempWordPosition = -1;

    while (true) {

        std::cin >> tempWordPosition;

        // checks whether an error has occurred
        bool anErrorHasOccurred = std::cin.fail();

        if (tempWordPosition <= 0 || tempWordPosition > wordCount || anErrorHasOccurred) {

            std::cin.clear();
            std::cin.ignore(AMOUNT_OF_CHARACTERS_TO_SKIP, '\n');

            std::cout << "Please enter a valid word position, between 1 and " << wordCount << ": ";
            continue;
        }

        break;
    }

    *wordPosition = tempWordPosition;
}

bool getIndexOfWordOnGivenPosition(const char* text, const char* corruptChars, unsigned int wordPosition, unsigned int &wordIndex) {

    if (text == nullptr) return false;
    if (text[0] == '\0') return false;

    int currentIndex = 0;
    int wordCount = 0;

    while (true) {

        // to check if a char is a letter we have to see if it's a normal letter or if it was corrupted
        if (isLetter(text[currentIndex]) || corruptChars[currentIndex] != '\0') {

            // we've encountered a word
            wordCount++;

            // if this is the word we're looking for we exit
            if (wordCount == wordPosition) break;

            // this loops skips to the character after the word
            while (true) {

                // move to the next index
                currentIndex++;

                // if we've reached a non letter character we exit
                if (!isLetter(text[currentIndex]) && corruptChars[currentIndex] == '\0') break;

                // if we've reached the end of the text we exit
                if (text[currentIndex] == '\0') break;
            }

            // go to the previous before we increment it to the current in the next step
            currentIndex--;
        }

        // go to the next index
        currentIndex++;

        // if we reach the end of the text wwe exit
        if (text[currentIndex] == '\0') break;
    }

    // save the index
    wordIndex = currentIndex;

    // if we've reached the end of the text return false
    return text[currentIndex] != '\0';
}

bool getLengthOfWordStartingOnGivenIndex(const char* text, const char* corruptChars, unsigned int wordIndex, unsigned int &wordLength) {

    if (text == nullptr) return false;
    if (text[0] == '\0') return false;
    if (corruptChars == nullptr) return false;

    wordLength = 0;
    while (true) {

        // calculating currentIndex
        const unsigned int currentIndex = wordIndex + wordLength;

        if (text[currentIndex] == '\0') break;

        // check if we've reached end of the word(if a char is not a letter then both chars in text and corruptChars shouldn't be letters)
        if (!isLetter(text[currentIndex]) && corruptChars[currentIndex] == '\0') break;

        // incrementing to the next index
        wordLength++;
    }

    return true;
}

bool printWordStartingOnGivenIndex(const char* text, const char* corruptChars, unsigned int wordIndex, unsigned int wordLength) {

    if (text == nullptr) return false;
    if (text[0] == '\0') return false;
    if (corruptChars == nullptr) return false;

    unsigned int endIndex = wordIndex + wordLength;

    for (unsigned int currentIndex = wordIndex; currentIndex < endIndex; currentIndex++) {

        // printing uncorrupted character
        if (corruptChars[currentIndex] == '\0') {

            std::cout << text[currentIndex];
            continue;
        }

        // printing in green
        if (text[currentIndex] == corruptChars[currentIndex])
            std::cout << "\033[32m" << text[currentIndex] << "\033[0m";

        // printing in red
        if (text[currentIndex] != corruptChars[currentIndex])
            std::cout << "\033[31m" << text[currentIndex] << "\033[0m";
    }

    return true;
}

bool promptPrintSelectedWord(const char* text, const char* corruptChars, unsigned int wordIndex, unsigned int wordLength) {

    if (text == nullptr) return false;
    if (text[0] == '\0') return false;
    if (corruptChars == nullptr) return false;

    std::cout << "Selected word is: ";
    printWordStartingOnGivenIndex(text, corruptChars, wordIndex, wordLength);
    std::cout << std::endl;

    return true;
}

bool promptAskForCharacterPosition(const char* text, unsigned int wordLength, unsigned int* &charPosition) {

    if (text == nullptr) return false;
    if (text[0] == '\0') return false;

    std::cout << "Enter the number of the character in this word you wish to inspect(0 to cancel): ";
    std::cin >> *charPosition;

    //TODO decide if this is going to return true or false
    if (*charPosition == 0) return false;

    while (true) {

        bool anErrorHasOccurred = std::cin.fail();

        if (*charPosition < 0 || *charPosition > wordLength || anErrorHasOccurred) {

            std::cin.clear();
            std::cin.ignore(AMOUNT_OF_CHARACTERS_TO_SKIP, '\n');

            std::cout << "Please enter a valid position between 1 and " << wordLength << ", or 0 to cancel: ";
            std::cin >> *charPosition;
            continue;
        }

        break;
    }

    return true;
}