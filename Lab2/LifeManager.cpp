#include "LifeManager.h"

int LifeManager::getIteration() const {
    return iterationCounter;
}

void LifeManager::setAlive(int i, int j) {
    fieldManager.set(i, j, true);
    aliveCounter++;
}

void LifeManager::kill(int i, int j) {
    fieldManager.set(i, j, false);
    aliveCounter--;
}

std::vector<std::vector<bool>> LifeManager::getField() {
    return fieldManager.getField();
}

int LifeManager::getFieldSize() {
    return fieldManager.getSize();
}

bool LifeManager::checkSurviveNeighborhoods(int n) {
    for (int i: survivalState) {
        if (i == n) return true;
    }
    return false;
}

bool LifeManager::checkBirthNeighborhoods(int n) {
    for (int i: birthState) {
        if (i == n) return true;
    }
    return false;
}

bool LifeManager::iteration() {
    for (int i = 0; i < fieldManager.getSize(); ++i) {
        for (int j = 0; j < fieldManager.getSize(); ++j) {
            neighborhoods[i][j] = fieldManager.getCell(i - 1, j) + fieldManager.getCell(i - 1, j - 1) +
                                  fieldManager.getCell(i, j - 1) + fieldManager.getCell(i + 1, j) +
                                  fieldManager.getCell(i, j + 1) +
                                  fieldManager.getCell(i + 1, j + 1) + fieldManager.getCell(i + 1, j - 1) +
                                  fieldManager.getCell(i - 1, j + 1);
        }
    }
    for (int i = 0; i < fieldManager.getSize(); ++i) {
        for (int j = 0; j < fieldManager.getSize(); ++j) {
            bool keepAlive = fieldManager.getCell(i, j) and checkSurviveNeighborhoods(neighborhoods[i][j]);
            bool birthCell = (!fieldManager.getCell(i, j)) and checkBirthNeighborhoods(neighborhoods[i][j]);
            if (!fieldManager.getCell(i, j) and birthCell)
                setAlive(i, j);
            else if (fieldManager.getCell(i, j) and !keepAlive)
                kill(i, j);
        }
    }
    if (aliveCounter == 0) return false;
    iterationCounter++;
    return true;
}