#include <WAVFileManager.h>

namespace WAVFManager {
    WAVFileManager::WAVFileManager(std::string inputFileName, std::string outputFileName) {
        inputFileStream.open(inputFileName, std::ios::in | std::ios::binary);
        outputFileStream.open(outputFileName, std::ios::out | std::ios::binary);
    }

    bool WAVFileManager::readSample(std::vector<char> &inputSample) {
        return inputFileStream.read(&inputSample[0], inputSample.size()).eof();
    }

    void WAVFileManager::openSubSample(std::string inputFileName, size_t ignoreHeaderSymbols) {
        subFileStream.open(inputFileName, std::ios::in | std::ios::binary);
        subFileStream.ignore(ignoreHeaderSymbols);
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