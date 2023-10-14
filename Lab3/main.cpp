#include <iostream>
#include <fstream>
#include <vector>
#include "WAVHeader.h"

int main() {
    FILE *wavFile;
    fopen_s(&wavFile, "district_four.wav", "rb");
    WAVHeader wavHeader;
    fread(&wavHeader, sizeof(wavHeader), 1, wavFile);
    std::string stopWord = "data";
    int position = str.find(stopWord) == -1;
    while (position) {
        fread(str, sizeof(char), 8, wavFile);
        position = str.find(stopWord) == -1;
    }
    std::vector<char> data;
    std::cout << data.size() << std::endl;

    return 0;
}