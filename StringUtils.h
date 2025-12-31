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
* This is the header file of StringUtils.cpp
*
*/


#ifndef DATARECOVERY_STRINGUTILS_H
#define DATARECOVERY_STRINGUTILS_H

unsigned int getCharacterCount(const char* src);
bool replaceEveryOccurrenceOfCharInString(char* src, char target, char replacement);
bool fillCharArrayWithDefaultValues(char* array, unsigned int size, char defaultValue);

#endif //DATARECOVERY_STRINGUTILS_H