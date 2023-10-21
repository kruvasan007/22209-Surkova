#pragma once

#include <IConverter.h>

namespace Converter {
    class MuteConverter : public IConverter {
    private:
        size_t endPos_ = 0;
    public:
        void setUp(IConverterStruct iConverterStruct) override;

        void convert(SampleStream &sampleStream) override;
    };
}