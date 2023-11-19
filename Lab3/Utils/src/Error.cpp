#include "include/Errors.h"
#include <iostream>

namespace Error {
    size_t printError(const std::string& message, size_t id) {
        std::cerr << message << std::endl;
        return id;
    }
}