#pragma once

#include "../Errors.h"
#include "Configurator.h"
#include "Config.h"

namespace Configurator {
    size_t readConfigurationFile(const std::string &fileName, std::vector<Config> &configurations);
}