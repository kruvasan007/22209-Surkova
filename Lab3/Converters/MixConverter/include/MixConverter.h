#pragma once

#include <IConverter.h>
#include <string>
#include "Config.h"

namespace Converter {
    class MixConverter : public IConverter {
    private:
        void setUp(IConverterStruct iConverterStruct) override;

    public:
        size_t parseConfigString(std::string str) override;

        size_t convert(SampleStream &sampleStream) override;

    };
}
