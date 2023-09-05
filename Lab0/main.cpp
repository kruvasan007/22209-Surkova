#include <iostream>
#include <fstream>
#include <map>
#include <list>

#define INPUT_FILE_NAME 1
#define OUTPUT_FILE_NAME 2

using namespace std;

bool cmp(pair<string, int> &a, pair<string, int> &b) {
    return (a.second > b.second);
}

list<pair<string, int>> createList(map<string, int> &mapOfWords) {
    list<pair<string, int>> listOfWords;
    for (auto &item: mapOfWords) {
        listOfWords.emplace_back(item);
    }
    listOfWords.sort(cmp);
    return listOfWords;
}

void toLower(string &word) {
    for (char &c: word)
        c = tolower(static_cast<unsigned char>(c));
}

bool isLetter(unsigned char symbol) {
    return (symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z') || (symbol >= '0' && symbol <= '9');
}

void printOutput(const char *outputFileName, list<pair<string, int>> &outputData, int finallyCount) {
    string str = outputFileName;
    ofstream outputFile(str);
    for (const auto &pair: outputData) {
        outputFile << pair.first << ",";
        outputFile << pair.second << ",";
        outputFile << static_cast<int>(pair.second * 1.0 / finallyCount * 100) << "%\n";
    }
    outputFile.close();
}

void putWord(map<string, int> &mapOfWords, string currentString, int lastPos, int pos, int &wordsCount) {
    string word = currentString.substr(lastPos, pos - lastPos);
    toLower(word);
    if (mapOfWords.count(word) == 0)
        mapOfWords[word] = 1;
    else
        mapOfWords[word]++;
    wordsCount++;
}

void findWords(map<string, int> &mapOfWords, string currentString, int &wordsCount) {
    int pos = 0;
    int lastPos = 0;
    while (pos < currentString.length()) {
        if (!isLetter(currentString[pos])) {
            if (pos != lastPos)
                putWord(mapOfWords, currentString, lastPos, pos, wordsCount);
            lastPos = pos + 1;
        }
        pos++;
    }
    if (lastPos < currentString.length())
        putWord(mapOfWords, currentString, lastPos, pos, wordsCount);
}

int main(int argc, char **argv) {
    if (argc != 3) return 1;

    string str = argv[INPUT_FILE_NAME];
    ifstream inputFile(str);
    string currentString;
    map<string, int> mapOfWords;
    int wordsCount = 0;
    while (getline(inputFile, currentString))
        findWords(mapOfWords, currentString, wordsCount);
    inputFile.close();

    list<pair<string, int>> listOfWords = createList(mapOfWords);

    printOutput(argv[OUTPUT_FILE_NAME], listOfWords, wordsCount);

    return 0;
}