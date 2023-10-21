#pragma once

#include <IConverter.h>

namespace Converter {
    class MixConverter : public IConverter {
    public:
        void setUp(IConverterStruct iConverterStruct) override;

        void convert(SampleStream &sampleStream) override;
    };
}
