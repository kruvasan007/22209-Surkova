#pragma once

#include <string>
#include <vector>

typedef struct FileData {
    std::string name = "Basic";
    int size = 10;
    std::vector<int> Bs, Ss;
    std::vector <std::pair<int, int>> coords;
} FileData;
