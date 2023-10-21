#include <fstream>
#include "../Errors.h"
#include "../include/WAVHeaderParser.h"

size_t WAVHeaderParser::parseFileHeader(const std::string &fileName) {
    WAVHeader wavHeader{};
    std::string stopWord = "data";
    std::ifstream file(fileName);
    file.read((char *) &wavHeader, sizeof(WAVHeader));
    if (wavHeader.subchunk1Id != stopWord.c_str()) {
        std::string str(4096, 0);
        size_t isFindData = str == stopWord;
        while (!isFindData) {
            file.read(&str[0], 4096);
            isFindData = str.find(stopWord);
        }
        if (isFindData == -1) {
            return Error::printError(Error::ErrorContainer(Error::ERROR_PARSE_HEADER, Error::CODE_ERROR_PARSE_HEADER));
        } else {
            wavHeader.subchunk2Id[0] = 'd';
            wavHeader.subchunk2Id[1] = 'a';
            wavHeader.subchunk2Id[2] = 't';
            wavHeader.subchunk2Id[3] = 'a';
            wavHeader.dataPosition = isFindData + sizeof(WAVHeader) + stopWord.size() + 4;
            wavHeader.subchunk2Size[0] = str.c_str()[isFindData + 4];
            wavHeader.subchunk2Size[1] = str.c_str()[isFindData + 5];
            wavHeader.subchunk2Size[2] = str.c_str()[isFindData + 6];
            wavHeader.subchunk2Size[3] = str.c_str()[isFindData + 7];
        }
    } else {
        wavHeader.dataPosition = sizeof(WAVHeader);
    }
    headers.push_back(wavHeader);
    return 0;
}

WAVHeader &WAVHeaderParser::getWAVHeader(size_t id) {
    return headers[id];
}

