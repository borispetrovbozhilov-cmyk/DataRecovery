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
* This source file contains helper functions for working with strings
*
*/

#include "StringUtils.h"


// function that returns the count of characters in the string(without the '\0')
unsigned int getCharacterCount(const char* src) {

    if (src == nullptr) return 0;
    if (src[0] == '\0') return 0;

    unsigned int length = 0;
    while (src[length++] != '\0');

    return --length;
}

bool replaceEveryOccurrenceOfCharInString(char* src, char target, char replacement) {

    if (src == nullptr) return false;
    if (src[0] == '\0') return false;
    if (target == '\0') return false;
    if (replacement == '\0') return false;

    for (unsigned int i = 0; src[i] != '\0'; i++) {
        if (src[i] == target) {
            src[i] = replacement;
        }
    }

    return true;
}