#pragma once

#include "../Converters/IConverter/StreamReader.h"
#include "WAVHeaderParser.h"
#include <fstream>
#include <memory>
#include <vector>

namespace WAVFManager {
    class WAVStreamReader : public Converter::StreamReader {
    private:
        size_t size_stream;
        std::vector<std::ifstream> inputFileStream;
    public:
        WAVStreamReader(const std::vector<std::string> &inputFileNames,
                        std::unique_ptr<WAVHeaderParser> &wavHeaderParser);

        std::vector<char> getStream(std::size_t idx);
    };
}
