#include "WAVStreamReader.h"

namespace WAVFManager {
    WAVStreamReader::WAVStreamReader(const std::vector<std::string> &inputFileNames,
                                     std::unique_ptr<WAVHeaderParser> &wavHeaderParser) {
        size_stream = wavHeaderParser->getWAVHeader(0).byteRate;
        for (int i = 0; i < inputFileNames.size(); ++i) {
            inputFileStream.push_back(std::ifstream{});
            inputFileStream[i].open(inputFileNames[i], std::ios::in | std::ios::binary);
            inputFileStream[i].ignore(wavHeaderParser->getWAVHeader(i).dataPosition);
        }
    }

    std::vector<char> WAVStreamReader::getStream(std::size_t idx) {
        std::vector<char> stream(size_stream);
        if (inputFileStream[idx].read(&(stream[0]), stream.size()).eof())
            stream.resize(0);
        return stream;
    }
}