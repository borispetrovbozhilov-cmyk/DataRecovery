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
* This source file holds the logic for the corruption and colouring of the text
*
*/

#include "TextCorruption.h"

#include <iostream>

#include "FileHandling.h"

unsigned int getCountOfCorruptCharacters(double corruptionRate, unsigned int textLength) {

    if (corruptionRate < 0 || corruptionRate > 1) return 0;

    return corruptionRate * textLength + 0.5;
}
