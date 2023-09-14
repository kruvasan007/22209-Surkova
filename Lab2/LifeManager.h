#pragma once

#include <string>
#include <vector>
#include "FieldManager.h"

class LifeManager {
private:
    std::vector<int> birthState;
    std::string gameName;
    int iterationCounter;
    int aliveCounter;
    std::vector<int> survivalState;
    std::vector<std::vector<int>> neighborhoods;
    FieldManager fieldManager;
public:

    LifeManager(std::vector<int> Bs, std::vector<int> Ss, int fieldSize = 10) {
        birthState = std::move(Bs);
        survivalState = std::move(Ss);
        fieldManager = FieldManager(fieldSize);
        neighborhoods.resize(fieldManager.getSize());
        for (int i = 0; i < fieldManager.getSize(); ++i)
            neighborhoods[i].resize(fieldManager.getSize());
        aliveCounter = 0;
        iterationCounter = 0;
    }

    int getIteration() const;

    void setAlive(int i, int j);

    std::vector<std::vector<bool>> getField();

    int getFieldSize();

    void kill(int i, int j);

    bool checkSurviveNeighborhoods(int n);

    bool checkBirthNeighborhoods(int n);

    bool iteration();

};