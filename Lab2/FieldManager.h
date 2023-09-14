#pragma once

#include <iostream>

class FieldManager {
private:
    size_t sizeFiled;
    bool **field;
public:
    FieldManager();

    explicit FieldManager(int N = 10) {

    }

    ~FieldManager();

};

