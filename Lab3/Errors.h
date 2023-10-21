#pragma once

#include <string>
#include <utility>
#include <iostream>

namespace Error {
    struct ErrorContainer {
        std::string message_;
        size_t codeError_;

        ErrorContainer(std::string msg, size_t codeError) {
            message_ = std::move(msg);
            codeError_ = codeError;
        }
    };

    const std::string ERROR_PARSE_HEADER = "ERROR: Unable to parse the file";
    const std::string ERROR_PARSE_CONFIG = "ERROR: Unable to parse the file";
    const std::string ERROR_CONVERTER = "ERROR: Impossible to convert a stream";
    const size_t CODE_ERROR_PARSE_HEADER = 1;
    const size_t CODE_ERROR_PARSE_CONFIG = 2;
    const size_t CODE_ERROR_CONVERTER = 3;

    size_t printError(const ErrorContainer &errorContainer);
}