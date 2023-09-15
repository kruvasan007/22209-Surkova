#include <iostream>
#include <string>
#include <list>
#include "CountWords.h"
#include "Letter.h"
#include "WordData.h"

CountWords::CountWords() {
    totalCount = 0;
}

double CountWords::calculatePercent(int frequency) const {
    return (frequency * 1.0 / totalCount * 100);
}

void CountWords::putWord(const std::string &currentString, int lastPos, int pos) {
    std::string word = currentString.substr(lastPos, pos - lastPos);
    toLower(word);
    mapOfWords[word]++;
    totalCount++;
}

std::list<wordData> CountWords::createList() {
    std::list<wordData> listOfWords;
    for (const auto &item: mapOfWords) {
        listOfWords.emplace_back(wordData(item.first, item.second));
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

void CountWords::printOutput(const std::string &outputFileName, std::list<wordData> &outputData) {
    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        std::cout << "Error: File isn't open" << std::endl;
        return;
    }

    for (const auto &item: outputData) {
        outputFile << item.word << ",";
        outputFile << item.frequency << ",";
        outputFile << calculatePercent(item.frequency) << "%\n";
    }
}

bool operator<(const wordData &a, const wordData &b) {
    return (a.frequency < b.frequency);
}

void CountWords::getCSV(const std::string &inputFileName, const std::string &outputFileName) {

    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        std::cout << "Error: File isn't open" << std::endl;
        return;
    }
    std::string currentString;
    while (getline(inputFile, currentString))
        findWords(currentString);

    std::list<wordData> listOfWords = createList();

    printOutput(outputFileName, listOfWords);
}