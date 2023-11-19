#pragma once

#include "FactoryAliasNames.h"

namespace Factory {
    IFactoryPtr createFactory(FactoryMap factoryMap);
}
