#pragma once

typedef struct Cell {
    bool state;
    int *neighborhoods;
} Cell;