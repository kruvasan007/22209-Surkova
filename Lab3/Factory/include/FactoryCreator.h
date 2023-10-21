#pragma once

#include "AliasNames.h"

namespace Factory {
    IFactoryPtr createFactory(FactoryMap factoryMap);
}
