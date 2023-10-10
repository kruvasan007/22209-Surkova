#pragma once

#include <vector>

enum class CellState {
    Dead,
    Alive,
};

class FieldManager {
private:
    std::size_t sizeFiled;

    std::vector<CellState> field;

    std::size_t calculatePosition(int i, int j) const;

public:
    FieldManager(std::size_t n = 10);

    void set(std::size_t i, std::size_t j, CellState state);

    std::size_t getSize() const;

    bool isCellAlive(int i, int j) const;
};

