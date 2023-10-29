#pragma once

#include <IConverter.h>

namespace Converter {
    class FlexConverter : public IConverter {
    private:
        size_t duration_;
        bool currentState = false;

        void setUp(IConverterStruct iConverterStruct) override;

    public:

        size_t parseConfigString(std::string str) override;

        size_t convert(SampleStream &sampleStream) override;
    };
}
