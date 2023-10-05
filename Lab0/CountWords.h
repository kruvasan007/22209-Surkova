#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "CountWords.h"
#include "Letter.h"
#include "WordData.h"

const size_t inputFileNameIdx = 1;
const size_t outputFileNameIdx = 2;

class CountWords {
private:
    size_t totalCount;
    std::map<std::string, int> mapOfWords;

    double calculatePercent(int frequency) const;

    std::list<wordData> createList();

    void printOutput(const std::string &outputFileName, std::list<wordData> &outputData);

    void putWord(const std::string &currentString, int lastPos, int pos);

    void findWords(std::string currentString);

    bool checkFileOpen(std::ifstream file);

public:
    CountWords();

    void getCSV(const std::string &inputFileName, const std::string &outputFileName);
};

bool operator<(const wordData &a, const wordData &b);
