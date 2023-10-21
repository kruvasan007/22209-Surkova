#pragma once

#include "../Factory/include/Tag.h"
#include "../Factory/include/AliasNames.h"
#include "IConverter/AliasNames.h"

namespace Converter {
    const Factory::Tag<Converter::IConverterPtr> muteConverterTag{"mute"};
    const Factory::Tag<Converter::IConverterPtr> mixConverterTag{"mix"};
    const Factory::Tag<Converter::IConverterPtr> flexConverterTag{"flex"};
}