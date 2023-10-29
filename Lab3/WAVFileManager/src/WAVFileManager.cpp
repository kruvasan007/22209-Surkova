#include <WAVFileManager.h>
#include "../Errors.h"

namespace WAVFManager {
    WAVFileManager::WAVFileManager(const std::string& inputFileName, const std::string& outputFileName) {
        inputFileStream.open(inputFileName, std::ios::in | std::ios::binary);
        outputFileStream.open(outputFileName, std::ios::out | std::ios::binary);
        if (!inputFileStream.is_open() or !outputFileStream.is_open()) {
            Error::printError(Error::ERROR_FILE_OPEN, Error::CODE_ERROR_FILE_OPEN);
        }
    }

    bool WAVFileManager::readSample(std::vector<char> &inputSample) {
        return inputFileStream.read(&inputSample[0], inputSample.size()).eof();
    }

    bool WAVFileManager::openSubSample(std::string inputFileName, size_t ignoreHeaderSymbols) {
        subFileStream.open(inputFileName, std::ios::in | std::ios::binary);
        subFileStream.ignore(ignoreHeaderSymbols);
        return subFileStream.is_open();
    }

    bool WAVFileManager::readSubSample(std::vector<char> &inputSample) {
        return subFileStream.read(&inputSample[0], inputSample.size()).eof();
    }

    void WAVFileManager::writeHeader(const WAVHeader &wavHeader) {
        inputFileStream.ignore(wavHeader.dataPosition);

        outputFileStream.write((char *) &wavHeader, sizeof(WAVHeader) - sizeof(unsigned long));
    }

    void WAVFileManager::writeSample(std::vector<char> &outputSample) {
        outputFileStream.write(&outputSample[0], outputSample.size());
    }
}