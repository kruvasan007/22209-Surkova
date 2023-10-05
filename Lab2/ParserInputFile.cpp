#include "ParserInputFile.h"

namespace {
    int toInt(char c) {
        return c - '0';
    }
}

bool ParserInputFile::readFile(const std::string &fName, GameParams &gameParams) {
    std::ifstream inputFile(fName);

    if (!inputFile.is_open()) {
        std::cout << "Error: File isn't open" << std::endl;
        return false;
    }
    std::string currentString;
    while (getline(inputFile, currentString)) {
        if (currentString.empty()) {
            std::cout << "Error: Invalid file" << std::endl;
            return false;
        }
        parseString(currentString, gameParams);
    }
    return true;
}

void ParserInputFile::parseString(std::string str, GameParams &gameParams) {
    char firstSymbol = str[0];
    if (firstSymbol == '#') {
        char modification = str[1];
        if (modification == 'N') {
            gameParams.name = str.substr(NAME_POS, str.length());
        } else if (modification == 'R') {
            readRule(str, gameParams);
        } else if (modification == 'S') {
            readSize(str, gameParams);
        } else {
            return;
        }
    } else if ('9' >= firstSymbol and firstSymbol >= '0') {
        gameParams.firstCells.push_back(getCoords(str));
    }
}

bool ParserInputFile::readSize(std::string str, GameParams &gameParams) {
    int lastPos = SIZE_POS;
    int pos = SIZE_POS;
    while (str[pos] != '\n' && pos < str.length()) {
        pos++;
    }
    gameParams.size = std::stoi(str.substr(lastPos, pos - lastPos));
    return true;
}

bool ParserInputFile::readRule(std::string str, GameParams &gameParams) {
    int pos = 1;
    while (str[pos] != 'B' && pos < str.length())
        pos++;
    if (pos == str.length()) {
        std::cout << "Error: No rules. Use standard" << std::endl;
        return false;
    }
    pos++;
    while (str[pos] != '/') {
        if ('9' >= str[pos] and str[pos] >= '0')
            gameParams.Bs[toInt(str[pos])] = true;
        else {
            std::cout << "Error: Wrong rules number" << std::endl;
            return false;
        }
        pos++;
    }
    while (str[pos] != 'S' && pos < str.length())
        pos++;
    pos++;
    while (pos < str.length()) {
        if ('9' >= str[pos] and str[pos] >= '0')
            gameParams.Ss[toInt(str[pos])] = true;
        else {
            std::cout << "Error: Wrong rules number" << std::endl;
            return false;
        }
        pos++;
    }
    return true;
}

Coords ParserInputFile::getCoords(std::string str) {
    int lastPos = 0, pos = 1;
    int count = 0;
    Coords crds;
    while (pos <= str.length()) {
        if (str[pos] == ' ' && count == 0) {
            crds.x = std::stoi(str.substr(lastPos, pos - lastPos));
            lastPos = pos + 1;
            count++;
        } else if (str[pos] == ' ' or str[pos] == '\n' or pos == str.length()) {
            crds.y = std::stoi(str.substr(lastPos, pos - lastPos));
            break;
        }
        pos++;
    }
    return crds;
}
