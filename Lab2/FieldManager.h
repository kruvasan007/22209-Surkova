#include <vector>

#pragma once

enum class CellState {
    Dead,
    Alive,
};

class FieldManager {
private:
    std::size_t sizeFiled;
    std::vector<CellState> field;

    std::size_t calculatePosition(std::size_t i, std::size_t j);

    void checkBoundaries(std::size_t &i);

public:

    FieldManager(std::size_t n = 10);

    std::vector<CellState> &getField();

    void set(std::size_t i, std::size_t j, CellState state);

    std::size_t getSize() const;

    bool isCellAlive(std::size_t i, std::size_t j);
};

