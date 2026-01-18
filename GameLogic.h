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
* This is the header file of GameLogic.cpp
*
*/


#ifndef DATARECOVERY_GAMELOGIC_H
#define DATARECOVERY_GAMELOGIC_H

constexpr unsigned int BUFFER_SIZE = 10000;

// NOTE functions only for printing information to the console
bool printCorruptedText(const char* text, const char* corruptChars);
bool printWordStartingOnGivenIndex(const char* text, const char* corruptChars, unsigned int wordIndex, unsigned int wordLength);
bool printArrowToChosenCharacterPosition(unsigned int chosenCharPosition, unsigned int wordLength);
void printEndGameMessage(unsigned int userMistakes);
bool printStatisticsOnTop(unsigned int correctlyGuessedChars, unsigned int userMistakes);

// NOTE functions that extract information and save it into a variable
bool getIndexOfWordOnGivenPosition(const char* text, const char* corruptChars, unsigned int wordPosition, unsigned int &wordIndex);
bool getLengthOfWordStartingOnGivenIndex(const char* text, const char* corruptChars, unsigned int wordIndex, unsigned int &wordLength);
unsigned int getWordCountOfText(const char* text);
unsigned int getCountOfLettersInText(const char* text);

// NOTE functions that print prompts in the console:
// asks the user for a word to edit and saves his choice into a variable
bool promptAskUserToChooseWord(unsigned int* wordPosition, unsigned int wordCount);

// only prints the word that the user has chosen
bool promptPrintSelectedWord(const char* text, const char* corruptChars, unsigned int wordIndex, unsigned int wordLength);

// asks the user for and saves into a variable the position of the character that he wishes to change
bool promptAskForCharacterPosition(const char* text, const char* corruptChars, unsigned int wordLength, unsigned int wordIndex, unsigned int* charPosition);

// only prints the options of chars that user has to chose from
bool promptPrintCharVariationsToChooseFrom(const char* charVariations);

// asks the user for the variation and saves his choice into a variable
void promptAskUserToPickCharVariation(unsigned short* charVariation);

// NOTE bool functions for checking state
bool checkIfUserChoseTheCorrectCharVariation(const char* corruptedChars, unsigned int chosenCharIndex, char chosenChar, bool &isCorrect);
bool checkIfNumberIsInArray(const unsigned int* array, unsigned int size, unsigned int target);
bool isLetter(char target);

// NOTE functions that run different states of the game-loop
bool stateWordSelection(const char* text, const char* corruptChars, unsigned int wordCount, unsigned int* wordPosition, unsigned int &wordIndex, unsigned int &wordLength);
bool stateCharacterSelection(const char* text, const char* corruptChars, unsigned int* charPosition, unsigned int wordIndex, unsigned int wordLength,
    unsigned int &chosenCharIndex, char &chosenChar);
bool stateChoosingOption(const char*  text, const char* corruptChars, unsigned int wordIndex,
    unsigned int wordLength, const unsigned int* charPosition, char* charVariations,
    char chosenChar, unsigned short* chosenCharVariationNumber, char &chosenCharVariation);
bool stateValidatingChoice(char* text, const char* corruptChars, unsigned int chosenCharIndex,
    char chosenCharVariation, unsigned int &correctlyGuessedChars, unsigned int &userMistakes, bool &userHasChosenCorrectVariation);

// NOTE main function that constructs the game and runs the game loop
bool play(bool &backToMainMenu, char* text, const char* corruptChars, unsigned int corruptedCharsCount, unsigned int wordCount,
    unsigned int &userMistakes, unsigned int &correctlyGuessedChars);

// NOTE functions that display the menus and UI and set up the game
void startGameMenu();
void startNewGameMenu();
void startNewGame(const char* filePath, double corruptionRate);
void loadSavedGameMenu();
bool loadSavedGame(const char* filePath);

// NOTE utility functions
void clearConsoleWindow();
void clearStreamBuffer();

void updateSaveFileToCurrentGame(const char* filePath, unsigned int textLength, const char* text, const char* corruptChars,
    unsigned int countOfCorrupted, unsigned int userMistakes, unsigned int correctlyGuessed);
void saveCurrentGameIntoNewSaveFile(unsigned int textLength, const char* text, const char* corruptChars,
    unsigned int countOfCorrupted, unsigned int userMistakes, unsigned int correctlyGuessed);

#endif //DATARECOVERY_GAMELOGIC_H