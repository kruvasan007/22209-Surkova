#include <FlexConverter.h>

namespace Converter {
    void FlexConverter::setUp(Converter::IConverterStruct iConverterStruct) {
        duration_ = iConverterStruct.duration;
    }

    void FlexConverter::convert(SampleStream &sampleStream) {
        if (currentState) {
            sampleStream[0] = sampleStream[1];
        }
        if (secondCounter_ % duration_ == 0) currentState = !currentState;
        secondCounter_++;
    }
}