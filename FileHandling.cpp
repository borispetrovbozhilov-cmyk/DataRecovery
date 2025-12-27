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

unsigned int getTextLengthFromFile(const char* fileName) {

    // validation
    if (fileName == nullptr) return 0;

    std::ifstream srcFile(fileName);

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



