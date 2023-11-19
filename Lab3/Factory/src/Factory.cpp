#include "Factory.h"

namespace Factory {

    Factory::Factory(FactoryMap factory_map) : factory_map_{std::move(factory_map)} {}

    std::optional<std::any> Factory::createInstance(const std::string &id) {
        auto it = factory_map_.find(id);
        if (it != factory_map_.end()) {
            return it->second();
        }
        return std::nullopt;
    }

}