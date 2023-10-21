#include <MuteConverter.h>
#include <vector>

namespace Converter {
    void MuteConverter::setUp(Converter::IConverterStruct iConverterStruct) {
        startPos_ = iConverterStruct.startPos;
        endPos_ = iConverterStruct.endPos;
    }

    void MuteConverter::convert(SampleStream &sampleStream) {
        if (secondCounter_ >= startPos_ and secondCounter_ < endPos_)
            std::fill(sampleStream[idStream_].begin(), sampleStream[idStream_].end(), 0);
        secondCounter_++;
    }
}