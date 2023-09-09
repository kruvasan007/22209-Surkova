#include <iostream>
#include <string>
#include <list>
#include "CountWords.h"
#include "Letter.h"

using namespace std;

CountWords::CountWords() {
    totalCount = 0;
}

double CountWords::calculatePercent(int frequency) {
    return (frequency * 1.0 / totalCount * 100);
}

void CountWords::putWord(const std::string &currentString, int lastPos, int pos) {
    string word = currentString.substr(lastPos, pos - lastPos);
    toLower(word);
    mapOfWords[word]++;
    totalCount++;
}

list<pair<string, int>> CountWords::createList() {
    list<pair<string, int>> listOfWords;
    for (auto &item: mapOfWords) {
        listOfWords.emplace_back(item);
    }
    listOfWords.sort();
    return listOfWords;
}

void CountWords::findWords(std::string currentString) {
    int pos = 0;
    int lastPos = 0;
    while (pos < currentString.length()) {
        if (!isLetter(currentString[pos])) {
            if (pos != lastPos)
                putWord(currentString, lastPos, pos);
            lastPos = pos + 1;
        }
        pos++;
    }
    if (lastPos < currentString.length())
        putWord(currentString, lastPos, pos);
}

void CountWords::printOutput(const std::string &outputFileName, list<pair<std::string, int>> &outputData) {
    ofstream outputFile(outputFileName);
    for (const auto &pair: outputData) {
        outputFile << pair.first << ",";
        outputFile << pair.second << ",";
        outputFile << calculatePercent(pair.second) << "%\n";
    }
    outputFile.close();
}

bool operator<(const pair<string, int> &a, const pair<string, int> &b) {
    return (a.second < b.second);
}

void CountWords::getCSV(const std::string &inputFileName, const std::string &outputFileName) {
    ifstream inputFile(inputFileName);
    if (inputFile.is_open())
        cout << "File is open" << endl;
    else {
        cout << "Error: File isn't open" << endl;
        return;
    }
    string currentString;
    while (getline(inputFile, currentString))
        findWords(currentString);
    inputFile.close();

    list<pair<string, int>> listOfWords = createList();

    printOutput(outputFileName, listOfWords);
}