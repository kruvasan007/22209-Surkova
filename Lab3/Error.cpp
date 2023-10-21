#include "Errors.h"

namespace Error {
    size_t printError(const ErrorContainer &errorContainer) {
        std::cerr << errorContainer.message_ << std::endl;
        return errorContainer.codeError_;
    }
}