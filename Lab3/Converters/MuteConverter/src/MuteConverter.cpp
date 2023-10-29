#include <MuteConverter.h>
#include <vector>
#include "../../../Errors.h"

namespace Converter {

    size_t MuteConverter::parseConfigString(std::string str) {
        size_t curPosition = str.find("mute");
        IConverterStruct iConverterStruct;
        curPosition += 5;
        size_t lastPos = curPosition;
        if (str[curPosition] >= '0' and str[curPosition] <= '9') {
            while (str[curPosition] != ' ' && curPosition < str.size())
                curPosition++;
            iConverterStruct.startPos = std::stoi(str.substr(lastPos, curPosition - lastPos));
        } else {
            Error::printError(Error::ERROR_PARSE_CONFIG, Error::CODE_ERROR_PARSE_CONFIG);
            return Error::CODE_ERROR_PARSE_CONFIG;
        }
        curPosition++;
        lastPos = curPosition;
        if (str[curPosition] >= '0' and str[curPosition] <= '9') {
            while (str[curPosition] != ' ' && curPosition < str.size())
                curPosition++;
            if (curPosition == lastPos) return 1;
            iConverterStruct.endPos = std::stoi(str.substr(lastPos, curPosition - lastPos));
        } else
            return Error::printError(Error::ERROR_PARSE_CONFIG, Error::CODE_ERROR_PARSE_CONFIG);
        setUp(iConverterStruct);
        return 0;
    }

    void MuteConverter::setUp(Converter::IConverterStruct iConverterStruct) {
        startPos_ = iConverterStruct.startPos;
        endPos_ = iConverterStruct.endPos;
    }

    size_t MuteConverter::convert(SampleStream &sampleStream) {
        if (secondCounter_ >= startPos_ and secondCounter_ < endPos_)
            std::fill(sampleStream[idStream_].begin(), sampleStream[idStream_].end(), 0);
        secondCounter_++;
        return 0;
    }
}