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

//TODO ask to use this global variable
const unsigned int AMOUNT_OF_CHARACTERS_TO_SKIP = 10000;

// NOTE functions only for printing information to the console
bool printCorruptedText(const char* text, const char* corruptChars);
bool printWordStartingOnGivenIndex(const char* text, const char* corruptChars, unsigned int wordIndex, unsigned int wordLength);

// NOTE functions that extract information and save it into a variable
bool getIndexOfWordOnGivenPosition(const char* text, const char* corruptChars, unsigned int wordPosition, unsigned int &wordIndex);
bool getLengthOfWordStartingOnGivenIndex(const char* text, const char* corruptChars, unsigned int wordIndex, unsigned int &wordLength);
unsigned int getWordCountOfText(const char* text);
unsigned int getCountOfLettersInText(const char* text);

// NOTE functions that print prompts in the console:
// asks the user for a word to edit and saves his choice into a variable
void promptAskUserToChooseWord(unsigned int* const &wordPosition, unsigned int wordCount);

// only prints the word that the user has chosen
bool promptPrintSelectedWord(const char* text, const char* corruptChars, unsigned int wordIndex, unsigned int wordLength);

// asks the user for and saves into a variable the position of the character that he wishes to change
bool promptAskForCharacterPosition(const char* text, const char* corruptChars, unsigned int wordLength, unsigned int wordIndex, unsigned int* &charPosition);

// only prints the options of chars that user has to chose from
bool promptPrintCharVariationsToChooseFrom(char* charVariations);

// asks the user for the variation and saves his choice into a variable
bool promptAskUserToPickCharVariation(unsigned short* charVariation);

// NOTE bool functions for checking state
bool checkIfUserChoseTheCorrectCharVariation(const char* corruptedChars, unsigned int chosenCharIndex, char chosenChar, bool &isCorrect);
bool checkIfNumberIsInArray(const unsigned int* array, unsigned int size, unsigned int target);
bool isLetter(char target);

// NOTE functions that run different states of the game-loop
bool stateWordSelection(const char* text, const char* corruptChars, const unsigned int wordCount, unsigned int* const &wordPosition, unsigned int &wordIndex, unsigned int &wordLength);
bool stateCharacterSelection(const char* text, const char* corruptChars, unsigned int* const &charPosition, const unsigned int wordIndex, const unsigned int wordLength,
    unsigned int &chosenCharIndex, char &chosenChar);
bool stateChoosingOption(char* const charVariations, const char chosenChar, unsigned short* const & chosenCharVariationNumber, char &chosenCharVariation);
bool stateValidatingChoice(char* text, const char* corruptChars, const unsigned int chosenCharIndex,
    const char chosenCharVariation, unsigned int &correctlyGuessedChars, unsigned int &userMistakes, bool &userHasChosenCorrectVariation);
bool stateEndOfStage(const unsigned int correctlyGuessedChars, const unsigned int userMistakes);

// NOTE main function that constructs the game and runs the game loop
bool play(char* text, char* corruptChars, unsigned int corruptedCharsCount, unsigned int wordCount, unsigned int &userMistakes);


#endif //DATARECOVERY_GAMELOGIC_H