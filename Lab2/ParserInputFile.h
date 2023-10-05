#pragma once

#include "Coords.h"
#include "GameParams.h"
#include <iostream>
#include <fstream>

const int SIZE_POS = 3;
const int NAME_POS = 3;

class ParserInputFile {
private:
    void parseString(std::string basicString, GameParams &gameParams);

    bool readRule(std::string basicString, GameParams &gameParams);

    bool readSize(std::string basicString, GameParams &gameParams);

    Coords getCoords(std::string basicString);

public:
    bool readFile(const std::string &fName, GameParams &gameParams);
};

