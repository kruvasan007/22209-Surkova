#pragma once

#include <IConverter.h>
#include "include/WAVStreamReader.h"

namespace Converter {
    class FlexConverter : public IConverter {
    private:
        size_t duration_;
        bool currentState = false;

        void setUp(IConverterStruct iConverterStruct) override;

    public:
        size_t parseConfigString(std::string str) override;

        size_t
        convert(std::vector<char> &stream, std::shared_ptr<StreamReader> &streamReader) override;
    };
}
