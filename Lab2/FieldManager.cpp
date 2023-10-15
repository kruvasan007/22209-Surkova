#pragma once

#include "FieldManager.h"

std::size_t FieldManager::calculatePosition(int i, int j) const {
    int iCorrect = i > 0 ? i % sizeField : (sizeField + i) % sizeField;
    int jCorrect = j > 0 ? j % sizeField : (sizeField + j) % sizeField;
    return iCorrect * sizeField + jCorrect;
}

FieldManager::FieldManager(std::size_t n) {
    sizeField = n;
    field.resize(sizeField * sizeField);
}

void FieldManager::set(std::size_t i, std::size_t j, CellState state) {
    field[calculatePosition(i, j)] = state;
}

bool FieldManager::isCellAlive(int i, int j) const {
    return field[calculatePosition(i, j)] == CellState::Alive;
}

std::size_t FieldManager::getSize() const {
    return sizeField;
}
