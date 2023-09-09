#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "CountWords.h"
#include "Letter.h"

#define INPUT_FILE_NAME 1
#define OUTPUT_FILE_NAME 2

using namespace std;

class CountWords {
private:
    size_t totalCount;
    map<string, int> mapOfWords;

    double calculatePercent(int frequency);

    list<pair<string, int>> createList();

    void printOutput(const string &outputFileName, list<pair<string, int>> &outputData);

    void putWord(const string &currentString, int lastPos, int pos);

    void findWords(string currentString);

public:
    CountWords();

    void getCSV(const string &inputFileName, const string &outputFileName);
};

bool operator<(const pair<string, int> &a, const pair<string, int> &b);
