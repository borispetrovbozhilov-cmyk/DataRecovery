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

bool printCorruptedText(const char* text, const char* corruptChars);
void promptAskUserToChooseWord(unsigned int* &wordPosition, unsigned int wordCount);
bool getIndexOfWordOnGivenPosition(const char* text, const char* corruptChars, unsigned int wordPosition, unsigned int &wordIndex);
bool getLengthOfWordStartingOnGivenIndex(const char* text, const char* corruptChars, unsigned int wordIndex, unsigned int &wordLength);
bool printWordStartingOnGivenIndex(const char* text, const char* corruptChars, unsigned int wordIndex, unsigned int wordLength);
bool promptPrintSelectedWord(const char* text, const char* corruptChars, unsigned int wordIndex, unsigned int wordLength);
bool promptAskForCharacterPosition(const char* text, unsigned int wordLength, unsigned int* &charPosition);
bool promptPrintCharVariationsToChooseFrom(char* charVariations);
bool promptAskUserToPickCharVariation(unsigned short* charVariation);
bool checkIfUserChoseTheCorrectCharVariation(const char* corruptedChars, unsigned int chosenCharIndex, char chosenChar, bool &isCorrect);

bool play(char* text, char* corruptChars, unsigned int corruptedCharsCount, unsigned int wordCount, unsigned int &userMistakes);

#endif //DATARECOVERY_GAMELOGIC_H