#include "FieldManager.h"

FieldManager::FieldManager(int n) {
    sizeFiled = n;
    field.resize(sizeFiled);
    for (int i = 0; i < sizeFiled; ++i) {
        field[i].resize(sizeFiled);
    }
}

void FieldManager::set(int i, int j, bool state) {
    if (i == sizeFiled) i = 0;
    if (i == -1) i = sizeFiled - 1;
    if (j == sizeFiled) j = 0;
    if (j == -1) j = sizeFiled - 1;
    field[i][j] = state;
}

std::vector<std::vector<bool>> &FieldManager::getField() {
    return field;
}

int FieldManager::getCell(int i, int j) {
    if (i == sizeFiled) i = 0;
    if (i == -1) i = sizeFiled - 1;
    if (j == sizeFiled) j = 0;
    if (j == -1) j = sizeFiled - 1;
    return field[i][j] ? 1 : 0;
}

int FieldManager::getSize() const {
    return sizeFiled;
}
