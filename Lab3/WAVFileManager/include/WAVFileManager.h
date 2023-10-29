#pragma once

#include <vector>
#include <fstream>
#include "WAVHeader.h"

namespace WAVFManager {
    class WAVFileManager {
    private:
        std::ifstream inputFileStream;
        std::ofstream outputFileStream;
        std::ifstream subFileStream;
    public:
        WAVFileManager(const std::string& inputFileName, const std::string& outputFileName);

        bool readSample(std::vector<char> &inputSample);

        bool readSubSample(std::vector<char> &inputSample);

        bool openSubSample(std::string inputFileName, size_t ignoreHeaderSymbols);

        void writeHeader(const WAVHeader &wavHeader);

        void writeSample(std::vector<char> &outputSample);
    };
}
