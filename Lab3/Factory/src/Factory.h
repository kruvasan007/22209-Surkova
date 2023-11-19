#pragma once

#include "../include/IFactory.h"

namespace Factory {
    class Factory :
            public IFactory,
            public std::enable_shared_from_this<Factory> {
    public:
        Factory(FactoryMap factory_map);

    private:
        std::optional<std::any> createInstance(const std::string &id) override;

        const FactoryMap factory_map_;
    };
}