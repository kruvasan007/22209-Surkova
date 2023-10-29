#include <MixConverter.h>
#include "../../Errors.h"

namespace Converter {
    size_t MixConverter::parseConfigString(std::string str) {
        size_t curPosition = str.find("mix");
        size_t input2;
        if (str[curPosition + 4] == '$') {
            curPosition += 5;
            input2 = str[curPosition] - '0';
        } else {
            Error::printError(Error::ERROR_PARSE_CONFIG, Error::CODE_ERROR_PARSE_CONFIG);
            return Error::CODE_ERROR_PARSE_CONFIG;
        }
        curPosition += 2;
        size_t lastPos = curPosition;
        while (str[curPosition] != '\n' && curPosition < str.size())
            curPosition++;
        IConverterStruct iConverterStruct;
        iConverterStruct.startPos = std::stoi(str.substr(lastPos, curPosition - lastPos));
        iConverterStruct.idStream = input2 - 1;
        setUp(iConverterStruct);
        return 0;
    }

    void MixConverter::setUp(Converter::IConverterStruct iConverterStruct) {
        startPos_ = iConverterStruct.startPos;
        idStream_ = iConverterStruct.idStream;
    }

    size_t MixConverter::convert(SampleStream &sampleStream) {
        if (secondCounter_ >= startPos_) {
            size_t i = 0;
            while (i < sampleStream[0].size()) {
                sampleStream[0][i] = (sampleStream[0][i] + sampleStream[idStream_][i]) / 2;
                i++;
            }
        }
        secondCounter_++;
        return 0;
    }
}