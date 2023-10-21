#include "../include/FactoryCreator.h"
#include "Factory.h"

namespace Factory {
    IFactoryPtr createFactory(FactoryMap factoryMap) {
        return std::make_shared<Factory>(std::move(factoryMap));
    }
}
