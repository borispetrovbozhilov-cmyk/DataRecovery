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
* This source file contains helper functions that are used later in the program for extracting data from files,
* as well as writing in files.
*
*/

#include <fstream>
#include "FileHandling.h"
#include "StringUtils.h"

unsigned int getTextLengthFromFile(const char* filePath) {

    // validation
    if (filePath == nullptr) return 0;

    std::ifstream srcFile(filePath);

    // validation
    if (!srcFile.is_open()) return 0;

    // file has successfully been opened

    // counting the number of characters in the source file, including '\n'
    srcFile.seekg(0, std::ios::end);
    const unsigned int length = srcFile.tellg();
    srcFile.seekg(0, std::ios::beg);

    //closing the stream
    srcFile.close();

    return length;
}

bool configureCorrectFilePath(char* filePath) {

    if (filePath == nullptr) return false;
    if (filePath[0] == '\0') return false;

    replaceEveryOccurrenceOfCharInString(filePath, '\\', '/');

    return true;
}

// TODO no way to control whether the text length doesn't exceed the array's size
bool extractTextFromFile(const char* filePath, char* text) {

    if (text == nullptr) return false;

    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) return false;

    int currentIndex = 0;
    char currentCharacter = 0;

    while (inputFile.get(currentCharacter)) {

        text[currentIndex] = currentCharacter;
        currentIndex++;
    }

    text[currentIndex] = '\0';

    inputFile.close();

    return true;
}



