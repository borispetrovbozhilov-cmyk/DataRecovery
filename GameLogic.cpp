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

    while (true) {

        //TODO decide if this is going to return true or false
        if (*charPosition == 0) return false;

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

bool promptPrintCharVariationsToChooseFrom(char* charVariations) {

    if (charVariations == nullptr) return false;

    unsigned short countOfCharVariations = 6;

    std::cout << "Choose what to change the selected character to: " << std::endl;

    std::cout << "0) Cancel" << std::endl;

    for (int i = 1; i <= countOfCharVariations; i++) {

        std::cout << i << ") " << charVariations[i] << std::endl;
    }

    return true;
}

bool promptAskUserToPickCharVariation(unsigned short* chosenCharVariationIndex) {

    unsigned short countOfCharVariations = 6;

    std::cout << "Your choice: ";
    std::cin >> *chosenCharVariationIndex;

    while (true) {

        // TODO decide if this is going to return true or false
        if (*chosenCharVariationIndex == 0) return false;

        // flag if an error has occurred in the stream(e.g. user entered a character instead of a digit)
        bool anErrorHasOccurred = std::cin.fail();

        // if the input was invalid the user would have to give new input
        if (*chosenCharVariationIndex > countOfCharVariations || anErrorHasOccurred) {

            // fixing the stream and clearing the input characters if there were any
            std::cin.clear();
            std::cin.ignore(AMOUNT_OF_CHARACTERS_TO_SKIP, '\n');

            // prompting user for new input
            std::cout << "Please pick a valid option between 1 and " << countOfCharVariations << ", or 0 to cancel: ";
            std::cin >> *chosenCharVariationIndex;

            // the loop continues until the user enters valid input
            continue;
        }

        // if the input was valid we exit the loop
        break;
    }

    return true;
}

bool checkIfUserChoseTheCorrectCharVariation(const char* corruptedChars, unsigned int chosenCharIndex, char chosenChar, bool &isCorrect) {

    if (corruptedChars == nullptr) return false;
    if (corruptedChars[chosenCharIndex] == '\0') return false;

    if (corruptedChars[chosenCharIndex] == chosenChar) isCorrect = true;
    else isCorrect = false;

    return true;
}

bool play(char* text, char* corruptChars, unsigned int corruptedCharsCount, unsigned int wordCount, unsigned int &userMistakes) {

    if (text == nullptr) return false;
    if (text[0] == '\0') return false;
    if (corruptChars == nullptr) return false;

    unsigned int* wordPosition = new unsigned int;
    unsigned int* charPosition = new unsigned int;
    unsigned short* chosenCharVariationIndex = new unsigned short;

    const unsigned short numberOfCharVariations = 6;

    unsigned int correctlyGuessedChars = 0;

    while (correctlyGuessedChars <= corruptedCharsCount) {

        printCorruptedText(text, corruptChars);
        //TESTING_printStringFromSize(corruptChars, textLength);

        //TODO make variables const where possible
        //TODO build logic if user chooses 0

        promptAskUserToChooseWord(wordPosition, wordCount);

        unsigned int wordIndex;
        getIndexOfWordOnGivenPosition(text, corruptChars, *wordPosition, wordIndex);

        unsigned int wordLength;
        getLengthOfWordStartingOnGivenIndex(text, corruptChars, wordIndex, wordLength);

        promptPrintSelectedWord(text, corruptChars, wordIndex, wordLength);

        //TODO validate that user has picked a corrupted character

        promptAskForCharacterPosition(text, wordLength, charPosition);

        const unsigned int chosenCharIndex = wordIndex + *charPosition - 1;
        char chosenChar = text[chosenCharIndex];

        char charVariations[numberOfCharVariations];

        generateCharVariationsFromCorruptedChar(charVariations, chosenChar);

        promptPrintCharVariationsToChooseFrom(charVariations);

        promptAskUserToPickCharVariation(chosenCharVariationIndex);

        const char chosenCharVariation = charVariations[*chosenCharVariationIndex];

        bool userHasChosenCorrectVariation = false;
        checkIfUserChoseTheCorrectCharVariation(corruptChars, chosenCharIndex, chosenCharVariation, userHasChosenCorrectVariation);

        if (userHasChosenCorrectVariation) {

            text[chosenCharIndex] = corruptChars[chosenCharIndex];
            correctlyGuessedChars++;
        }
        else userMistakes++;

        printCorruptedText(text, corruptChars);

        //TESTING_printStringFromSize(corruptChars, textLength);
    }

    delete wordPosition;
    delete charPosition;
    delete chosenCharVariationIndex;
}