#pragma once

#include <string>
#include <vector>
#include <bitset>
#include "Coords.h"

const int COUNT_OF_PREVIOUS_STATE = 9;

struct GameParams {
    std::string name = "Basic";
    std::string outputFileName;
    std::string rulesOfGame = "#R B3/S23";
    int size = 10;
    std::bitset<COUNT_OF_PREVIOUS_STATE> BirthdayCellsCount;
    std::bitset<COUNT_OF_PREVIOUS_STATE> SurviveCellCount;
    std::vector<Coords> firstCells;
};
