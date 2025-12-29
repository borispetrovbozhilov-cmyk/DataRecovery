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

unsigned int getCountOfCorruptCharacters(double corruptionRate, unsigned int textLength);

// function that returns a corrupted version of a given character
char corruptChar(char initial);

// function that generates random indexes and fills up the array without repetitions
bool getCorruptedIndexes(char* corruptIndexes, unsigned int size);

// function that goes through the text and corrupts the characters based on predetermined indexes + colouring
bool corruptText(char* text, char* corruptIndexes);

#endif //DATARECOVERY_TEXTCORRUPTION_H