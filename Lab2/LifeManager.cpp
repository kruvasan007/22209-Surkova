#include "LifeManager.h"

LifeManager::LifeManager(const GameParams &gameParams) {
    birthState = gameParams.BirthdayCellsCount;
    survivalState = gameParams.SurviveCellCount;
    fieldManager = FieldManager(gameParams.size);
    fieldManagerTemp = FieldManager(gameParams.size);
    for (auto item: gameParams.firstCells)
        setAlive(item.x, item.y);
    std::swap(fieldManager, fieldManagerTemp);
    fieldManagerTemp = fieldManager;
}

int LifeManager::getIteration() const {
    return iterationCounter;
}

void LifeManager::setAlive(size_t i, size_t j) {
    fieldManagerTemp.set(i, j, CellState::Alive);
    aliveCounter++;
}

void LifeManager::kill(size_t i, size_t j) {
    fieldManagerTemp.set(i, j, CellState::Dead);
    aliveCounter--;
}

const FieldManager &LifeManager::getField() const {
    return fieldManager;
}

bool LifeManager::checkSurviveNeighborhoods(size_t n) {
    return survivalState[n];
}

bool LifeManager::checkBirthNeighborhoods(size_t n) {
    return birthState[n];
}

bool LifeManager::nextIteration() {
    int countNeighborhoods;
    for (int i = 0; i < fieldManager.getSize(); ++i) {
        for (int j = 0; j < fieldManager.getSize(); ++j) {
            countNeighborhoods = fieldManager.isCellAlive(i - 1, j) + fieldManager.isCellAlive(i - 1, j - 1) +
                                 fieldManager.isCellAlive(i, j - 1) + fieldManager.isCellAlive(i + 1, j) +
                                 fieldManager.isCellAlive(i, j + 1) +
                                 fieldManager.isCellAlive(i + 1, j + 1) + fieldManager.isCellAlive(i + 1, j - 1) +
                                 fieldManager.isCellAlive(i - 1, j + 1);
            bool keepAlive = checkSurviveNeighborhoods(countNeighborhoods);
            bool birthCell = (!fieldManager.isCellAlive(i, j)) and checkBirthNeighborhoods(countNeighborhoods);
            if (birthCell)
                setAlive(i, j);
            else if (fieldManager.isCellAlive(i, j) and !keepAlive)
                kill(i, j);
        }
    }
    std::swap(fieldManager, fieldManagerTemp);
    fieldManagerTemp = fieldManager;
    if (aliveCounter == 0) return false;
    iterationCounter++;
    return true;
}