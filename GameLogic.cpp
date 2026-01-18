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
#include "StringUtils.h"
#include "FileHandling.h"

void clearConsoleWindow() {

    system("cls");
}

void clearStreamBuffer() {

    std::cin.clear();
    std::cin.ignore(BUFFER_SIZE, '\n');
}

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

bool promptAskUserToChooseWord(unsigned int* const wordPosition, const unsigned int wordCount) {

    if (wordPosition == nullptr) return false;
    if (wordCount == 0) return false;

    std::cout << "Enter the number of the word you wish to inspect(or 0 to go to main menu): ";

    // temporary variable to check if the entered number is negative
    long long tempCheckForSign = -1;

    while (true) {

        std::cin >> tempCheckForSign;

        // checks whether an error has occurred
        bool anErrorHasOccurred = std::cin.fail();

        if (!anErrorHasOccurred && tempCheckForSign == 0) {

            *wordPosition = 0;
            return true;
        }

        if (tempCheckForSign <= 0 || tempCheckForSign > wordCount || anErrorHasOccurred) {

            clearStreamBuffer();

            std::cout << "Please enter a valid word position, between 1 and " << wordCount << "(or 0 to go back to main menu): ";
            continue;
        }

        break;
    }

    *wordPosition = tempCheckForSign;

    return true;
}

bool getIndexOfWordOnGivenPosition(const char* text, const char* corruptChars, unsigned int wordPosition, unsigned int &wordIndex) {

    if (text == nullptr) return false;
    if (text[0] == '\0') return false;
    if (wordPosition == 0) return false;

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

bool promptAskForCharacterPosition(const char* text, const char* corruptChars, const unsigned int wordLength, const unsigned int wordIndex, unsigned int* const charPosition) {

    if (text == nullptr) return false;
    if (text[0] == '\0') return false;

    long long tempCheckForSign = -1;

    std::cout << "Enter the number of the character in this word you wish to inspect(0 to cancel): ";

    while (true) {

        // temporary variable, in which the input is saved at first, in order to check if negative number has been given as input
        std::cin >> tempCheckForSign;

        bool anErrorHasOccurred = std::cin.fail();

        bool hasChosenUncorruptedCharacter = false;

        if (!anErrorHasOccurred && tempCheckForSign >= 0) {

            if (tempCheckForSign == 0) {

                *charPosition = 0;
                return true;
            }

            unsigned int indexOfChosenChar = wordIndex + tempCheckForSign - 1;

            hasChosenUncorruptedCharacter = (corruptChars[indexOfChosenChar] == 0 ||
                corruptChars[indexOfChosenChar] == text[indexOfChosenChar]);
        }

        if (tempCheckForSign <= 0 || tempCheckForSign > wordLength || anErrorHasOccurred || hasChosenUncorruptedCharacter) {

            clearStreamBuffer();

            std::cout << "Please enter a valid position of a corrupted character between 1 and " << wordLength << ", or 0 to cancel: ";
            continue;
        }

        *charPosition = tempCheckForSign;

        break;
    }

    return true;
}

bool promptPrintCharVariationsToChooseFrom(const char* charVariations){

    if (charVariations == nullptr) return false;

    unsigned short countOfCharVariations = 6;

    std::cout << "Choose what to change the selected character to: " << std::endl;

    std::cout << "0) Cancel" << std::endl;

    for (int i = 0; i < countOfCharVariations; i++) {

        std::cout << i + 1 << ") " << charVariations[i] << std::endl;
    }

    return true;
}

void promptAskUserToPickCharVariation(unsigned short* const chosenCharVariationNumber) {

    unsigned short countOfCharVariations = 6;
    int tempCheckForSign = -1;

    std::cout << "Your choice: ";

    while (true) {

        std::cin >> tempCheckForSign;

        // flag if an error has occurred in the stream(e.g. user entered a character instead of a digit)
        bool anErrorHasOccurred = std::cin.fail();

        if (!anErrorHasOccurred) {

            if (tempCheckForSign == 0) {

                *chosenCharVariationNumber = 0;
                return;
            }

        }

        // if the input was invalid the user would have to give new input
        if (tempCheckForSign <= 0 || tempCheckForSign > countOfCharVariations || anErrorHasOccurred) {

            // fixing the stream and clearing the input characters if there were any
            clearStreamBuffer();

            // prompting user for new input
            std::cout << "Please pick a valid option between 1 and " << countOfCharVariations << ", or 0 to cancel: ";

            // the loop continues until the user enters valid input
            continue;
        }

        // if the input was valid we save the value of the temporary variable and exit the loop
        *chosenCharVariationNumber = tempCheckForSign;

        break;
    }
}

bool printArrowToChosenCharacterPosition(unsigned int chosenCharPosition, unsigned int wordLength) {

    if (chosenCharPosition > wordLength) return false;

    std::cout << "Selected char is: ";

    for (int i = 0; i < chosenCharPosition - 1; i++) {

        std::cout << " ";
    }

    std::cout << "^" << std::endl;

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

bool stateWordSelection(const char* text, const char* corruptChars, const unsigned int wordCount, unsigned int* const wordPosition, unsigned int &wordIndex, unsigned int &wordLength) {

    if (text == nullptr) return false;
    if (corruptChars == nullptr) return false;
    if (wordPosition == nullptr) return false;
    if (text[0] == 0) return false;
    if (wordCount <= 0) return false;

    // each stage starts by printing the current state of the text
    printCorruptedText(text, corruptChars);

    std::cout << std::endl;

    promptAskUserToChooseWord(wordPosition, wordCount);

    if (*wordPosition == 0) return true;

    getIndexOfWordOnGivenPosition(text, corruptChars, *wordPosition, wordIndex);

    getLengthOfWordStartingOnGivenIndex(text, corruptChars, wordIndex, wordLength);

    return true;
}

bool stateCharacterSelection(const char* text, const char* corruptChars, unsigned int* const charPosition, const unsigned int wordIndex, const unsigned int wordLength,
    unsigned int &chosenCharIndex, char &chosenChar) {

    if (text == nullptr) return false;
    if (corruptChars == nullptr) return false;
    if (charPosition == nullptr) return false;
    if (text[0] == 0) return false;

    //clearConsoleWindow();

    promptPrintSelectedWord(text, corruptChars, wordIndex, wordLength);

    std::cout << std::endl;

    promptAskForCharacterPosition(text, corruptChars, wordLength, wordIndex, charPosition);

    if (*charPosition == 0) return true;

    chosenCharIndex = wordIndex + *charPosition - 1;
    chosenChar = text[chosenCharIndex];

    return true;
}

bool stateChoosingOption(const char* const text, const char* const corruptChars, const unsigned int wordIndex,
    const unsigned int wordLength, const unsigned int* const charPosition, char* const charVariations,
    const char chosenChar, unsigned short* const chosenCharVariationNumber, char &chosenCharVariation) {

    if (charVariations == nullptr) return false;
    if (chosenChar <= 0) return false;

    //clearConsoleWindow();

    promptPrintSelectedWord(text, corruptChars, wordIndex, wordLength);
    printArrowToChosenCharacterPosition(*charPosition, wordLength);

    std::cout << std::endl;

    generateCharVariationsFromCorruptedChar(charVariations, chosenChar);

    promptPrintCharVariationsToChooseFrom(charVariations);

    promptAskUserToPickCharVariation(chosenCharVariationNumber);

    if (*chosenCharVariationNumber == 0) {

        chosenCharVariation = 0;
        return false;
    }

    // decreasing by one so it matches the index in the array
    chosenCharVariation = charVariations[*chosenCharVariationNumber - 1];

    return true;
}

bool stateValidatingChoice(char* text, const char* corruptChars, const unsigned int chosenCharIndex,
    const char chosenCharVariation, unsigned int &correctlyGuessedChars, unsigned int &userMistakes, bool &userHasChosenCorrectVariation) {

    if (text == nullptr) return false;
    if (corruptChars == nullptr) return false;
    if (text[0] == 0) return false;
    if (chosenCharVariation <= 0) return false;

    checkIfUserChoseTheCorrectCharVariation(corruptChars, chosenCharIndex, chosenCharVariation, userHasChosenCorrectVariation);

    if (userHasChosenCorrectVariation) {

        text[chosenCharIndex] = corruptChars[chosenCharIndex];
        correctlyGuessedChars++;
    }
    else {
        userMistakes++;
    }

    return true;
}

bool printStatisticsOnTop(const unsigned int correctlyGuessedChars, const unsigned int userMistakes) {

    // clearing the console
    clearConsoleWindow();

    std::cout << "Mistakes so far: " << userMistakes << std::endl;
    std::cout << "Correctly guessed so far: " << correctlyGuessedChars << std::endl;

    std::cout << std::endl;

    return true;
}

bool play(bool &backToMainMenu, char* text, const char* const corruptChars, const unsigned int corruptedCharsCount, const unsigned int wordCount,
    unsigned int &userMistakes, unsigned int &correctlyGuessedChars) {

    // validation
    if (text == nullptr) return false;
    if (text[0] == '\0') return false;
    if (corruptChars == nullptr) return false;

    // dynamic variables that are going to be needed
    unsigned int* wordPosition = new unsigned int;
    unsigned int* charPosition = new unsigned int;
    unsigned short* chosenCharVariationNumber = new unsigned short;

    // constant variables that are going to be needed
    constexpr unsigned short numberOfCharVariations = 6;

    // gameloop
    while (correctlyGuessedChars < corruptedCharsCount) {

        clearConsoleWindow();

        // NOTE state - word selection
        unsigned int wordIndex = 0;
        unsigned int wordLength = 0;

        printStatisticsOnTop(correctlyGuessedChars, userMistakes);
        stateWordSelection(text, corruptChars, wordCount, wordPosition, wordIndex, wordLength);

        // user has decided to go back to the main menu
        if (*wordPosition == 0) {
            backToMainMenu = true;

            delete wordPosition;
            delete charPosition;
            delete chosenCharVariationNumber;

            return true;
        }

        while (true) {

            // NOTE state - character selection
            unsigned int chosenCharIndex = 0;
            char chosenChar = 0;

            printStatisticsOnTop(correctlyGuessedChars, userMistakes);
            stateCharacterSelection(text, corruptChars, charPosition, wordIndex, wordLength, chosenCharIndex, chosenChar);

            if (*charPosition == 0) {

                clearConsoleWindow();
                break;
            }

            // NOTE state - choosing option
            char charVariations[numberOfCharVariations] = {0, 0, 0, 0, 0, 0};
            char chosenCharVariation = 0;

            printStatisticsOnTop(correctlyGuessedChars, userMistakes);
            stateChoosingOption(text, corruptChars, wordIndex, wordLength, charPosition,
                charVariations, chosenChar, chosenCharVariationNumber, chosenCharVariation);

            if (*chosenCharVariationNumber == 0) {

                clearConsoleWindow();
                continue;
            }

            // NOTE state - validating choice
            bool userHasChosenCorrectVariation = false;

            stateValidatingChoice(text, corruptChars, chosenCharIndex, chosenCharVariation, correctlyGuessedChars,
                                  userMistakes, userHasChosenCorrectVariation);

            // after choosing correctly the last corrupted character left, we exit the inner loop so we can end the game
            if (correctlyGuessedChars == corruptedCharsCount) break;
        }
    }

    printEndGameMessage(userMistakes);

    delete wordPosition;
    delete charPosition;
    delete chosenCharVariationNumber;

    return true;
}

void printEndGameMessage(const unsigned int userMistakes) {

    clearConsoleWindow();

    // user has completed the game
    std::cout << "Congratulations!" << std::endl;
    std::cout << "You have completed the game with " << userMistakes << " mistakes." << std::endl;
    std::cout << "Hope you enjoyed." << std::endl;
    std::cout << std::endl;
    std::cout << "Press enter to exit...";

    // waiting for user to press enter to close the program
    std::cin.get();
}

void startGameMenu() {

    clearConsoleWindow();

    std::cout << "\033[0;36m*---------------------*" << std::endl;
    std::cout << "*---\033[0m \033[1;37m\033[3mData Recovery\033[0m \033[0;36m---*" << std::endl;
    std::cout << "*---------------------*\033[0m" << std::endl;

    std::cout << std::endl;
    std::cout << "1. Start New Game" << std::endl;
    std::cout << "2. Load Saved Game" << std::endl;
    std::cout << std::endl;
    std::cout << "Choose an option: ";

    unsigned short menuChoice = 0;

    while (true) {

        std::cin >> menuChoice;
        clearStreamBuffer();

        if (menuChoice == 1) {
            startNewGameMenu();
            break;
        }

        if (menuChoice == 2) {
            loadSavedGameMenu();
            break;
        }

        std::cout << "Please choose a valid option: ";
    }
}

void startNewGameMenu() {

    clearConsoleWindow();

    constexpr unsigned short maxLengthOfFileName = BUFFER_SIZE;
    char filePath[maxLengthOfFileName];

    std::cout << "Please enter the file path or the name of the file: ";

    while (true) {

        std::cin.getline(filePath, BUFFER_SIZE);
        std::cout << std::endl;

        if (!std::cin.fail()) break;
        clearStreamBuffer();

        std::cout << "The path was too long or invalid. Please enter a new path: ";
    }

    std::cout << "Enter the corruption rate: ";

    double corruptionRate = 0;

    while (true) {

        std::cin >> corruptionRate;
        std::cout << std::endl;

        if (corruptionRate > 0 && corruptionRate < 1) break;
        clearStreamBuffer();

        std::cout << "Please enter a valid corruption rate between 0 and 1: ";
    }

    // configures the file path correctly so it can be read on all OS
    configureCorrectFilePath(filePath);

    startNewGame(filePath, corruptionRate);
}

void startNewGame(const char* filePath, const double corruptionRate) {

    clearConsoleWindow();

    // textLength is going to be a dynamic variable, since we will learn the path runtime
    const unsigned int textLength = getTextLengthFromFile(filePath);

    // we have to add one more element for the '\0'
    char* text = new char[textLength + 1];
    char* corruptChars = new char[textLength];

    // extracts the text and saves it into an array
    extractTextFromFile(filePath, text);

    // corruptChar must be filled with 0 by default because of logic
    fillCharArrayWithDefaultValues(corruptChars, textLength, 0);

    // getting count of corrupted character in the text
    unsigned int countOfCorrupted = getCountOfCorruptCharacters(text, corruptionRate);

    // generating the position of the corrupted characters
    generateCorruptedCharacters(corruptChars, countOfCorrupted, text, textLength);

    // corrupting the original text
    corruptText(text, corruptChars, textLength);

    // counter for user mistakes
    unsigned int userMistakes = 0;
    unsigned int correctlyGuessed = 0;

    // gets the count of the words
    const unsigned int wordCount = getWordCountOfText(text);

    // creating a flag if user decides to go back to main menu
    bool backToMainMenu = false;

    // plays the actual game
    play(backToMainMenu, text, corruptChars, countOfCorrupted, wordCount, userMistakes, correctlyGuessed);

    // going back to the main menu
    if (backToMainMenu) {

        clearConsoleWindow();

        saveCurrentGameIntoNewSaveFile(textLength, text, corruptChars, countOfCorrupted, userMistakes, correctlyGuessed);

        // freeing memory in order of allocating it
        delete[] text;
        delete[] corruptChars;

        startGameMenu();
    }

    // freeing memory in order of allocating it
    delete[] text;
    delete[] corruptChars;
}

void loadSavedGameMenu() {

    clearConsoleWindow();

    constexpr unsigned short maxLengthOfFileName = BUFFER_SIZE;
    char filePath[maxLengthOfFileName];

    std::cout << "Please enter the file path or the name of the file(with extension .datarecovery): ";

    while (true) {

        std::cin.getline(filePath, BUFFER_SIZE);

        if (!std::cin.fail()) {

            bool hasValidDataRecoveryExtension = false;
            hasDataRecoveryExtension(filePath, hasValidDataRecoveryExtension);

            //check for extension
            if (hasValidDataRecoveryExtension) break;
        }

        std::cout << "The path was too long or invalid. Please enter a new path: ";
    }

    configureCorrectFilePath(filePath);

    loadSavedGame(filePath);
}

bool loadSavedGame(const char* filePath) {

    if (filePath == nullptr) return false;

    unsigned int textLength = 0;
    unsigned int countOfCorrupted = 0;

    char* text;
    char* corruptChars;

    unsigned int userMistakes = 0;
    unsigned int correctlyGuessed = 0;

    extractGameSaveFromFile(filePath, textLength, text, corruptChars, userMistakes, correctlyGuessed, countOfCorrupted);

    const unsigned int wordCount = getWordCountOfText(text);

    bool backToMainMenu = false;

    play(backToMainMenu, text, corruptChars, countOfCorrupted, wordCount, userMistakes, correctlyGuessed);

    // going back to the main menu
    if (backToMainMenu) {

        clearConsoleWindow();

        updateSaveFileToCurrentGame(filePath, textLength, text, corruptChars, countOfCorrupted, userMistakes, correctlyGuessed);

        // freeing memory in order of allocating it
        delete[] text;
        delete[] corruptChars;

        startGameMenu();
    }

    // freeing memory in order of allocating it
    delete[] text;
    delete[] corruptChars;

    return true;
}

void updateSaveFileToCurrentGame(const char* filePath, const unsigned int textLength, const char* const text, const char* const corruptChars,
    const unsigned int countOfCorrupted, const unsigned int userMistakes, const unsigned int correctlyGuessed) {

    clearConsoleWindow();

    std::cout << "Do you want to update your saved game? Type y/n: ";

    char answer = 0;

    while (true) {

        std::cin >> answer;
        clearStreamBuffer();
        std::cout << std::endl;

        if (answer != 'y' && answer != 'n' && answer != 'Y' && answer != 'N') {

            std::cout << "Please enter y(for yes) or n(for no): ";
            continue;
        }

        break;
    }

    if (answer == 'y' || answer == 'Y') {

        const unsigned int filePathLength = getCharacterCount(filePath);
        char saveFileName[filePathLength];

        extractFileNameFromSaveFilePath(filePath, saveFileName);

        std::cout << saveFileName << std::endl;

        saveGameIntoFile(saveFileName, textLength, text, corruptChars, userMistakes, correctlyGuessed, countOfCorrupted);

        std::cout << std::endl;
        std::cout << "Your game was saved successfully!" << std::endl;
        std::cout << "Save name: " << saveFileName << ".datarecovery" << std::endl;

        std::cout << "Press enter to continue..." << std::endl;

        // waiting for user to press enter to close the program
        std::cin.get();
    }

}

void saveCurrentGameIntoNewSaveFile(const unsigned int textLength, const char* const text, const char* const corruptChars,
    const unsigned int countOfCorrupted, const unsigned int userMistakes, const unsigned int correctlyGuessed) {

    clearConsoleWindow();

    std::cout << "Do you want to save your game? Type y/n: ";

    char answer = 0;

    while (true) {

        std::cin >> answer;
        clearStreamBuffer();
        std::cout << std::endl;

        if (answer != 'y' && answer != 'n' && answer != 'Y' && answer != 'N') {

            std::cout << "Please enter y(for yes) or n(for no): ";
            continue;
        }

        break;
    }

    if (answer == 'y' || answer == 'Y') {

        std::cout << "Please enter a name for your save file: ";

        char saveFileName[BUFFER_SIZE];

        while (true) {

            std::cin.getline(saveFileName, BUFFER_SIZE);

            if (std::cin.fail()) {

                std::cout << "An error occurred. File name might be too long. Please enter a shorter one instead: ";
                continue;
            }

            break;
        }
        saveGameIntoFile(saveFileName, textLength, text, corruptChars, userMistakes, correctlyGuessed, countOfCorrupted);

        std::cout << std::endl;
        std::cout << "Your game was saved successfully!" << std::endl;
        std::cout << "Save name: " << saveFileName << ".datarecovery" << std::endl;

        std::cout << "Press enter to continue...";

        // waiting for user to press enter to close the program
        std::cin.get();

    }

}