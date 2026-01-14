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
* This is the header file of TextCorruption.cpp
*
*/

#ifndef DATARECOVERY_TEXTCORRUPTION_H
#define DATARECOVERY_TEXTCORRUPTION_H

// function that predetermines the number of corrupted characters in the text
unsigned int getCountOfCorruptCharacters(const char* text, double corruptionRate);

// function that returns a corrupted version of a given character
char corruptCharLetter(char initial);

// function that generates based on random indexes chooses which characters to be corrupted and saves them in an array
bool generateCorruptedCharacters(char* corruptChars, unsigned int countOfCorrupted, const char* text, unsigned int textLength);

// function that goes through the text and corrupts the characters based on predetermined indexes + colouring
bool corruptText(char* text, const char* corruptChars, unsigned int textLength);

bool checkIfThereAreEnoughLettersToCorruptInText(const char* text, double corruptionRate);

bool generateCharVariationsFromCorruptedChar(char* charVariations, char corruptedChar);

bool characterIsCorrupted(const char* text, const char* corruptChars, unsigned int charIndex);

// TESTING
char TEST_corruptCharFromGivenIndex(char initial, int bitPosition);

#endif //DATARECOVERY_TEXTCORRUPTION_H