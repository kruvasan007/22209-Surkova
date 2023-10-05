#pragma once

#include "FieldManager.h"

void FieldManager::checkBoundaries(std::size_t &i) {
    if (i == sizeFiled) i = 0;
    if (i == -1) i = sizeFiled - 1;
}

std::size_t FieldManager::calculatePosition(std::size_t i, std::size_t j) {
    return i * sizeFiled + j;
}

FieldManager::FieldManager(std::size_t n) {
    sizeFiled = n;
    field.resize(sizeFiled * sizeFiled);
}

void FieldManager::set(std::size_t i, std::size_t j, CellState state) {
    checkBoundaries(i);
    checkBoundaries(j);
    field[calculatePosition(i, j)] = state;
}

std::vector<CellState> &FieldManager::getField() {
    return field;
}

bool FieldManager::isCellAlive(std::size_t i, std::size_t j) {
    checkBoundaries(i);
    checkBoundaries(j);
    return field[calculatePosition(i, j)] == CellState::Alive;
}

std::size_t FieldManager::getSize() const {
    return sizeFiled;
}
