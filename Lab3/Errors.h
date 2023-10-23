#pragma once

#include <string>
#include <utility>
#include <iostream>

namespace Error {
    const std::string ERROR_PARSE_HEADER = "ERROR: Unable to parse the header of file";
    const std::string ERROR_PARSE_CONFIG = "ERROR: Unable to parse the file";
    const std::string ERROR_CONVERTER = "ERROR: Impossible to convert a stream";
    const std::string ERROR_PARSE_ARGUMENTS = "ERROR: Invalid arguments";
    const std::string ERROR_FILE_OPEN = "ERROR: File isn't open";

    const size_t CODE_ERROR_PARSE_HEADER = 1;
    const size_t CODE_ERROR_PARSE_CONFIG = 2;
    const size_t CODE_ERROR_CONVERTER = 3;
    const size_t CODE_ERROR_PARSE_ARGUMENTS = 4;
    const size_t CODE_ERROR_FILE_OPEN = 5;

    size_t printError(const std::string& message, size_t id);
}