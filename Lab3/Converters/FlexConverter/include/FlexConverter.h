#pragma once

#include <IConverter.h>

namespace Converter {
    class FlexConverter : public IConverter {
    private:
        size_t duration_;
        bool currentState = false;
    public:
        void setUp(IConverterStruct iConverterStruct) override;

        void convert(SampleStream &sampleStream) override;
    };
}
