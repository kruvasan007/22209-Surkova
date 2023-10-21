#include <MixConverter.h>
#include <iostream>

namespace Converter {
    void MixConverter::setUp(Converter::IConverterStruct iConverterStruct) {
        startPos_ = iConverterStruct.startPos;
        idStream_ = iConverterStruct.idStream;
    }

    void MixConverter::convert(SampleStream &sampleStream) {
        if (secondCounter_ >= startPos_) {
            size_t i = 0;
            while (i < sampleStream[0].size()) {
                sampleStream[0][i] = (sampleStream[0][i] + sampleStream[idStream_][i]) / 2;
                i++;
            }
        }
        secondCounter_++;
    }
}