#include <FlexConverter.h>
#include "../Errors.h"

namespace Converter {

    size_t FlexConverter::parseConfigString(std::string str) {
        size_t curPosition = str.find("flex");
        IConverterStruct iConverterStruct;
        curPosition += 5;
        size_t lastPos = curPosition;
        if (str[curPosition] >= '0' and str[curPosition] <= '9') {
            while (str[curPosition] != ' ' && curPosition < str.size())
                curPosition++;
            iConverterStruct.duration = std::stoi(str.substr(lastPos, curPosition - lastPos));
        } else
            return Error::printError(Error::ERROR_PARSE_CONFIG, Error::CODE_ERROR_PARSE_CONFIG);
        curPosition += 1;
        size_t input2;
        if (str[curPosition] == '$') {
            curPosition++;
            input2 = str[curPosition] - '0';
        } else
            return Error::printError(Error::ERROR_PARSE_CONFIG, Error::CODE_ERROR_PARSE_CONFIG);
        iConverterStruct.idStream = input2 - 1;
        setUp(iConverterStruct);
        return 0;
    }

    void FlexConverter::setUp(Converter::IConverterStruct iConverterStruct) {
        duration_ = iConverterStruct.duration;
    }

    size_t FlexConverter::convert(SampleStream &sampleStream) {
        if (sampleStream[0].size() != sampleStream[idStream_].size()) {
            Error::printError(Error::ERROR_CONVERTER, Error::CODE_ERROR_CONVERTER);
            return Error::CODE_ERROR_CONVERTER;
        }
        if (currentState) {
            sampleStream[0] = sampleStream[idStream_];
        }
        if (secondCounter_ % duration_ == 0) currentState = !currentState;
        secondCounter_++;
        return 0;
    }
}