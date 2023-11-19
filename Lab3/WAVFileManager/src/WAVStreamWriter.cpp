#include <WAVStreamWriter.h>
#include "../Utils/include/Errors.h"

namespace WAVFManager {
    WAVStreamWriter::WAVStreamWriter(const std::string &outputFileName) {
        outputFileStream.open(outputFileName, std::ios::out | std::ios::binary);
        if (!outputFileStream.is_open())
            Error::printError(Error::ERROR_FILE_OPEN, Error::CODE_ERROR_FILE_OPEN);
    }

    void WAVStreamWriter::writeHeader(const WAVHeader &wavHeader) {
        outputFileStream.write((char *) &wavHeader, sizeof(WAVHeader) - sizeof(unsigned long));
    }

    void WAVStreamWriter::writeSample(std::vector<char> &outputSample) {
        outputFileStream.write(&outputSample[0], outputSample.size());
    }
}