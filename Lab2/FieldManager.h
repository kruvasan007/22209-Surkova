#pragma once

#include <iostream>
#include <vector>

const size_t neighborhoodsCount = 8;

class FieldManager {
private:
    int sizeFiled;
    std::vector<std::vector<bool>> field;
public:
    FieldManager(int n = 10);

    std::vector<std::vector<bool>> &getField();

    void set(int i, int j, bool state);

    int getSize() const;

    int getCell(int i, int j);

};

