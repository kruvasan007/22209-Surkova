#pragma once

#include <string>
#include <vector>
#include <bitset>
#include "FieldManager.h"
#include "GameParams.h"

class LifeManager {
private:
    std::string gameName;
    int iterationCounter = 0;
    int aliveCounter = 0;
    std::bitset<COUNT_OF_PREVIOUS_STATE> birthState;
    std::bitset<COUNT_OF_PREVIOUS_STATE> survivalState;
    FieldManager fieldManager;
    FieldManager fieldManagerTemp;

    void kill(size_t i, size_t j);

    bool checkSurviveNeighborhoods(size_t n);

    bool checkBirthNeighborhoods(size_t n);

    void setAlive(size_t i, size_t j);

public:
    size_t getFieldSize() const;

    LifeManager(const GameParams &gameParams);

    int getIteration() const;

    const std::vector<CellState> &getField();

    bool nextIteration();

};