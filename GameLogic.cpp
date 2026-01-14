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

void promptAskUserToChooseWord(unsigned int* const &wordPosition, unsigned int wordCount) {

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

bool promptAskForCharacterPosition(const char* text, const char* corruptChars, unsigned int wordLength, unsigned int wordIndex, unsigned int* const &charPosition) {

    if (text == nullptr) return false;
    if (text[0] == '\0') return false;

    std::cout << "Enter the number of the character in this word you wish to inspect(0 to cancel): ";
    std::cin >> *charPosition;

    while (true) {

        //TODO decide if this is going to return true or false
        if (*charPosition == 0) return false;

        bool anErrorHasOccurred = std::cin.fail();

        unsigned int indexOfChosenChar = wordIndex + *charPosition - 1;
        bool hasChosenUncorruptedCharacter = (corruptChars[indexOfChosenChar] == 0 ||
            corruptChars[indexOfChosenChar] == text[indexOfChosenChar]);

        std::cout << *charPosition << std::endl;
        std::cout << text[indexOfChosenChar] << " : " << corruptChars[indexOfChosenChar] << std::endl;

        if (*charPosition <= 0 || *charPosition > wordLength || anErrorHasOccurred || hasChosenUncorruptedCharacter) {

            std::cin.clear();
            std::cin.ignore(AMOUNT_OF_CHARACTERS_TO_SKIP, '\n');

            std::cout << "Please enter a valid position of a corrupted character between 1 and " << wordLength << ", or 0 to cancel: ";
            std::cin >> *charPosition;
            continue;
        }

        break;
    }

    return true;
}

bool promptPrintCharVariationsToChooseFrom(char* charVariations){

    if (charVariations == nullptr) return false;

    unsigned short countOfCharVariations = 6;

    std::cout << "Choose what to change the selected character to: " << std::endl;

    std::cout << "0) Cancel" << std::endl;

    for (int i = 0; i < countOfCharVariations; i++) {

        std::cout << i + 1 << ") " << charVariations[i] << std::endl;
    }

    return true;
}

bool promptAskUserToPickCharVariation(unsigned short* const chosenCharVariationNumber) {

    unsigned short countOfCharVariations = 6;

    std::cout << "Your choice: ";
    std::cin >> *chosenCharVariationNumber;

    while (true) {

        // TODO decide if this is going to return true or false
        if (*chosenCharVariationNumber== 0) return false;

        // flag if an error has occurred in the stream(e.g. user entered a character instead of a digit)
        bool anErrorHasOccurred = std::cin.fail();

        // if the input was invalid the user would have to give new input
        if (*chosenCharVariationNumber< 0 || *chosenCharVariationNumber> countOfCharVariations || anErrorHasOccurred) {

            // fixing the stream and clearing the input characters if there were any
            std::cin.clear();
            std::cin.ignore(AMOUNT_OF_CHARACTERS_TO_SKIP, '\n');

            // prompting user for new input
            std::cout << "Please pick a valid option between 1 and " << countOfCharVariations << ", or 0 to cancel: ";
            std::cin >> *chosenCharVariationNumber;

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

bool isLetter(char target) {

    return (target >= 'a' && target <= 'z') || (target >= 'A' && target <= 'Z');
}

bool stateWordSelection(const char* text, const char* corruptChars, const unsigned int wordCount, unsigned int* const &wordPosition, unsigned int &wordIndex, unsigned int &wordLength) {

    if (text == nullptr) return false;
    if (corruptChars == nullptr) return false;
    if (wordPosition == nullptr) return false;
    if (text[0] == 0) return false;
    if (wordCount <= 0) return false;

    // state - word selection:
    // params - text, corruptedChars, wordCount, wordPosition
    // return vars - wordIndex, wordLength
    promptAskUserToChooseWord(wordPosition, wordCount);

    getIndexOfWordOnGivenPosition(text, corruptChars, *wordPosition, wordIndex);

    getLengthOfWordStartingOnGivenIndex(text, corruptChars, wordIndex, wordLength);

    promptPrintSelectedWord(text, corruptChars, wordIndex, wordLength);

    // end of state
    return true;
}

bool stateCharacterSelection(const char* text, const char* corruptChars, unsigned int* const &charPosition, const unsigned int wordIndex, const unsigned int wordLength,
    unsigned int &chosenCharIndex, char &chosenChar) {

    if (text == nullptr) return false;
    if (corruptChars == nullptr) return false;
    if (charPosition == nullptr) return false;
    if (text[0] == 0) return false;

    // state - character selection
    promptAskForCharacterPosition(text, corruptChars, wordLength, wordIndex, charPosition);

    chosenCharIndex = wordIndex + *charPosition - 1;
    chosenChar = text[chosenCharIndex];

    // end of state
    return true;
}

bool stateChoosingOption(char* const charVariations, const char chosenChar, unsigned short* const & chosenCharVariationNumber, char &chosenCharVariation) {

    if (charVariations == nullptr) return false;
    if (chosenChar <= 0) return false;

    // state - choosing option

    generateCharVariationsFromCorruptedChar(charVariations, chosenChar);

    promptPrintCharVariationsToChooseFrom(charVariations);

    promptAskUserToPickCharVariation(chosenCharVariationNumber);

    // FIXME if user chooses 0 to cancel an error occurs since it tries to enters the array with an index of -1
    // decreasing by one so it matches the index in the array
    chosenCharVariation = charVariations[*chosenCharVariationNumber - 1];

    // end of state
    return true;
}

bool stateValidatingChoice(char* text, const char* corruptChars, const unsigned int chosenCharIndex,
    const char chosenCharVariation, unsigned int &correctlyGuessedChars, unsigned int &userMistakes, bool &userHasChosenCorrectVariation) {

    if (text == nullptr) return false;
    if (corruptChars == nullptr) return false;
    if (text[0] == 0) return false;
    if (chosenCharVariation <= 0) return false;

    checkIfUserChoseTheCorrectCharVariation(corruptChars, chosenCharIndex, chosenCharVariation, userHasChosenCorrectVariation);

    // FIXME if user decides to cancel his choice don't increase userMistakes
    if (userHasChosenCorrectVariation) {

        text[chosenCharIndex] = corruptChars[chosenCharIndex];
        correctlyGuessedChars++;
    }
    else {
        // NOTE ask about whether it has to be updated to the wrong char
        // text[chosenCharIndex] = chosenCharVariation;
        userMistakes++;
    }

    return true;
}

bool stateEndOfStage(const unsigned int correctlyGuessedChars, const unsigned int userMistakes) {

    if (correctlyGuessedChars == 0) return false;

    std::cout << correctlyGuessedChars << " : " << userMistakes << std::endl;

    //TODO clear console so every stage of the game has its own window:
    //system("cls");

    return true;
}

bool play(char* text, char* const corruptChars, unsigned int corruptedCharsCount, unsigned int wordCount, unsigned int &userMistakes) {

    // validation
    if (text == nullptr) return false;
    if (text[0] == '\0') return false;
    if (corruptChars == nullptr) return false;

    // dynamic variables that are going to be needed
    unsigned int* wordPosition = new unsigned int;
    unsigned int* charPosition = new unsigned int;
    unsigned short* chosenCharVariationNumber= new unsigned short;

    // static variables that are going to be needed
    constexpr unsigned short numberOfCharVariations = 6;
    unsigned int correctlyGuessedChars = 0;

    // gameloop
    while (correctlyGuessedChars < corruptedCharsCount) {

        // each stage starts by printing the current state of the text
        printCorruptedText(text, corruptChars);

        //TESTING_printStringFromSize(corruptChars, textLength);

        //TODO make variables const where possible
        //TODO build logic if user chooses 0

        // NOTE state - word selection
        unsigned int wordIndex;
        unsigned int wordLength;

        stateWordSelection(text, corruptChars, wordCount, wordPosition, wordIndex, wordLength);

        // NOTE state - character selection
        unsigned int chosenCharIndex = 0;
        char chosenChar = 0;

        stateCharacterSelection(text, corruptChars, charPosition, wordIndex, wordLength, chosenCharIndex, chosenChar);

        // NOTE state - choosing option
        char charVariations[numberOfCharVariations] = {0, 0, 0, 0, 0, 0};
        char chosenCharVariation = 0;

        stateChoosingOption(charVariations, chosenChar, chosenCharVariationNumber, chosenCharVariation);

        // NOTE state - validating choice
        bool userHasChosenCorrectVariation = false;

        stateValidatingChoice(text, corruptChars, chosenCharIndex, chosenCharVariation, correctlyGuessedChars,
                              userMistakes, userHasChosenCorrectVariation);

        // NOTE state - end of stage statistic and console clearing
        stateEndOfStage(correctlyGuessedChars, userMistakes);

        //TESTING_printStringFromSize(corruptChars, textLength);
    }

    delete wordPosition;
    delete charPosition;
    delete chosenCharVariationNumber;

    return true;
}