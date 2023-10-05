#pragma once

#include <string>

typedef struct wordData {
    std::string word;
    int frequency;

    wordData(std::string w, int f) {
        word = w;
        frequency = f;
    }
} wordData;
