#pragma once

#include <string>
#include <IConverterStruct.h>
#include <Tags.h>

namespace Configurator {
    struct Config {
        Factory::Tag<Converter::IConverterPtr> tag;
        Converter::IConverterStruct iConverterStruct{};
    };
}
