#pragma once

#include <string>
#include <vector>

typedef struct FileData {
    std::string name;
    int size;
    std::vector<int> Bs, Ss;
    std::vector<std::pair<int, int>> coords;
} FileData;
