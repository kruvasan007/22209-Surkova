#pragma once

#include "FieldManager.h"

std::size_t FieldManager::calculatePosition(int i, int j) const {
    int iCorrect = i > 0 ? i % sizeFiled : (sizeFiled + i) % sizeFiled;
    int jCorrect = j > 0 ? j % sizeFiled : (sizeFiled + j) % sizeFiled;
    return iCorrect * sizeFiled + jCorrect;
}

FieldManager::FieldManager(std::size_t n) {
    sizeFiled = n;
    field.resize(sizeFiled * sizeFiled);
}

void FieldManager::set(std::size_t i, std::size_t j, CellState state) {
    field[calculatePosition(i, j)] = state;
}

bool FieldManager::isCellAlive(int i, int j) const {
    return field[calculatePosition(i, j)] == CellState::Alive;
}

std::size_t FieldManager::getSize() const {
    return sizeFiled;
}
