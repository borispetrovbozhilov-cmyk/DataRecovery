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
#include <iostream>
#include "FileHandling.h"
#include "StringUtils.h"


unsigned int getTextLengthFromFile(const char* filePath) {

    // validation
    if (filePath == nullptr) return 0;

    std::ifstream srcFile(filePath);

    // validation
    if (!srcFile.is_open()) return 0;

    // file has successfully been opened

    unsigned int length = 0;

    char currentChar = 0;
    while (srcFile.get(currentChar)) {

        if (currentChar == '\r') continue;
        length++;
    }

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

bool extractFileNameFromSaveFilePath(const char* filePath, char* fileName) {

    if (filePath == nullptr) return false;
    if (fileName == nullptr) return false;

    constexpr unsigned int extensionLength = 13;
    const unsigned int filePathLength = getCharacterCount(filePath);

    unsigned int extensionStartIndex = filePathLength - extensionLength;

    unsigned int nameStartIndex = extensionStartIndex;

    // iterating until we get to the index before the start of the name of the file
    while ((filePath[nameStartIndex] != '/') && (filePath[nameStartIndex] != '\\') && nameStartIndex != 0) {

        nameStartIndex--;
    }

    // moving it forward once it matches the start of the word if it found a \ or /
    if (nameStartIndex != 0) nameStartIndex++;

    // extracting the name
    for (unsigned int i = nameStartIndex; i < extensionStartIndex; i++) {

        fileName[i - nameStartIndex] = filePath[i];
    }

    fileName[extensionStartIndex] = '\0';

    return true;
}

bool saveGameIntoFile(const char* fileName, const unsigned int textLength, const char* text, const char* corruptChars,
    const unsigned int userMistakes, const unsigned int correctlyGuessed, const unsigned int countOfCorrupted) {

    if (fileName == nullptr) return false;
    if (text == nullptr) return false;
    if (corruptChars == nullptr) return false;
    if (text[0] == 0) return false;

    constexpr char nameExtension[] = ".datarecovery";

    const unsigned int originalFileNameLength = getCharacterCount(fileName);
    const unsigned int nameExtensionLength = getCharacterCount(nameExtension);

    const unsigned int saveGameFileNameLength = originalFileNameLength + nameExtensionLength + 1;

    char saveGameFileName[saveGameFileNameLength];

    fillCharArrayWithDefaultValues(saveGameFileName, saveGameFileNameLength, 0);

    concatenateStringsIntoTheFirstOne(saveGameFileName, fileName);
    concatenateStringsIntoTheFirstOne(saveGameFileName, nameExtension);

    std::ofstream saveGameFile(saveGameFileName);

    if (!saveGameFile.is_open()) return false;

    saveGameFile << textLength << std::endl;

    saveGameFile << text << std::endl;

    for (int i = 0; i < textLength; i++) {

        saveGameFile << corruptChars[i];
    }
    saveGameFile << std::endl;

    saveGameFile << userMistakes << std::endl;
    saveGameFile << correctlyGuessed << std::endl;

    saveGameFile << countOfCorrupted << std::endl;

    saveGameFile.close();

    return true;
}

bool extractGameSaveFromFile(const char* saveGameFileName, unsigned int &textLength, char* &text, char* &corruptChars,
    unsigned int &userMistakes, unsigned int &correctlyGuessed, unsigned int &countOfCorrupted) {

    //validation
    if (saveGameFileName == nullptr) return false;
    if (text == nullptr) return false;
    if (corruptChars == nullptr) return false;

    std::ifstream loadGameSaveFile(saveGameFileName);

    if (!loadGameSaveFile.is_open()) return false;

    //a variable that is going to be used only for moving the cursor
    char tempForMovingCursor = '\0';

    // each function from bellow extracts an element from the save file in the order they've been saved

    getNumberFromLineInFile(loadGameSaveFile, textLength);

    //NOTE allocating memory that is going to be freed outside of the function
    text = new char[textLength + 1];
    corruptChars = new char[textLength];

    getTextFromFileByLength(loadGameSaveFile, text, textLength);

    // setting the end of the text, because the function doesn't do it
    text[textLength] = '\0';

    std::cout << text << std::endl;

    // moving the cursor to the next line
    loadGameSaveFile.get(tempForMovingCursor);

    getTextFromFileByLength(loadGameSaveFile, corruptChars, textLength);

    // moving the cursor to the next line
    loadGameSaveFile.get(tempForMovingCursor);

    getNumberFromLineInFile(loadGameSaveFile, userMistakes);

    getNumberFromLineInFile(loadGameSaveFile, correctlyGuessed);

    getNumberFromLineInFile(loadGameSaveFile, countOfCorrupted);

    loadGameSaveFile.close();
    return true;
}

bool getNumberFromLineInFile(std::ifstream &loadGameSaveFile, unsigned int &number) {

    if (!loadGameSaveFile.is_open()) return false;

    number = 0;
    char digit = '\0';

    while (loadGameSaveFile.get(digit)) {

        if (digit == '\n') break;

        number = number * 10 + (digit - '0');
    }

    return true;
}

//NOTE the function doesn't set the terminating '\0' at the end
bool getTextFromFileByLength(std::ifstream &loadGameSaveFile, char* text, const unsigned int textLength) {

    if (!loadGameSaveFile.is_open()) return false;
    if (text == nullptr) return false;
    if (textLength == 0) return false;

    // a variable pointing to the character that we have just extracted with get()
    char currentCharacter = '\0';

    // getting the text character by character
    for (int i = 0; i < textLength; i++) {

        // extracting character
        loadGameSaveFile.get(currentCharacter);

        // assigning it on its position
        text[i] = currentCharacter;
    }

    return true;
}

bool hasDataRecoveryExtension(const char* filePath, bool &check) {

    if (filePath == nullptr) return false;

    constexpr char validExtension[] = ".datarecovery";
    const unsigned int extensionLength = getCharacterCount(validExtension);

    const unsigned int filePathLength = getCharacterCount(filePath);

    if (filePathLength <= extensionLength) return false;

    const unsigned int filePathExtensionStartIndex = filePathLength - extensionLength;

    for (int i = 0; i < extensionLength; i++) {

        if (filePath[filePathExtensionStartIndex + i] != validExtension[i]) {

            check = false;
            return true;
        }
    }

    check = true;
    return true;
}


