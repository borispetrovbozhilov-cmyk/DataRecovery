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
* This is the header file of FileHandling.cpp
*
*/


#ifndef DATARECOVERY_FILEHANDLING_H
#define DATARECOVERY_FILEHANDLING_H

// Function declarations

unsigned int getTextLengthFromFile(const char* filePath);
bool configureCorrectFilePath(char* filePath);
bool extractTextFromFile(const char* filePath, char* text);
bool extractFileNameFromSaveFilePath(const char* filePath, char* fileName);

bool saveGameIntoFile(const char* fileName, unsigned int textLength, const char* text, const char* corruptChars,
    unsigned int userMistakes, unsigned int correctlyGuessed, unsigned int countOfCorrupted);
bool extractGameSaveFromFile(const char* saveGameFileName, unsigned int &textLength, char* &text, char* &corruptChars,
    unsigned int &userMistakes, unsigned int &correctlyGuessed, unsigned int &countOfCorrupted);

bool getNumberFromLineInFile(std::ifstream &loadGameSaveFile, unsigned int &number);
bool getTextFromFileByLength(std::ifstream &loadGameSaveFile, char* text, unsigned int textLength);

bool hasDataRecoveryExtension(const char* filePath, bool &check);

#endif //DATARECOVERY_FILEHANDLING_H