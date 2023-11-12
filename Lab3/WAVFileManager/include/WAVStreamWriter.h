#pragma once

#include <vector>
#include <fstream>
#include "WAVHeader.h"

namespace WAVFManager {
    class WAVStreamWriter {
    private:
        std::ofstream outputFileStream;
    public:
        WAVStreamWriter(const std::string &outputFileName);

        void writeHeader(const WAVHeader &wavHeader);

        void writeSample(std::vector<char> &outputSample);
    };
}
