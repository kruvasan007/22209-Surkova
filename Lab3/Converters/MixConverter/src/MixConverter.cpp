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
        iConverterStruct.idStreams.push_back(input2 - 1);
        setUp(iConverterStruct);
        return 0;
    }

    void MixConverter::setUp(Converter::IConverterStruct iConverterStruct) {
        startPos_ = iConverterStruct.startPos;
        idStream_ = iConverterStruct.idStreams;
        countOfStreams = iConverterStruct.idStreams.size();
    }

    size_t
    MixConverter::convert(std::vector<char> &stream, std::shared_ptr<StreamReader> &streamReader) {
        SampleStream sampleStream(countOfStreams);
        for (int i = 0; i < countOfStreams; ++i) {
            sampleStream[i] = streamReader->getStream(idStream_[i]);
        }
        if (secondCounter_ >= startPos_) {
            for (int j = 0; j < countOfStreams; ++j) {
                size_t i = 0;
                while (i < stream.size()) {
                    stream[i] = (stream[i] + sampleStream[j][i]) / 2;
                    i++;
                }
            }
        }
        secondCounter_++;
        return 0;
    }
}