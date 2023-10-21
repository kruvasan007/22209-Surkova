#pragma once

#include <memory>
#include <string>
#include <any>
#include <map>
#include <functional>
#include "IFactory.h"

namespace Factory {
    struct IFactory;
    using IFactoryPtr = std::shared_ptr<IFactory>;
    using Creator = std::function<std::any()>;
    using FactoryMap = std::map<std::string, Creator>;
}