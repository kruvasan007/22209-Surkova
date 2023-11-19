#pragma once

#include "WAVHeader.h"
#include <string>
#include <vector>

class WAVHeaderParser {
private:
    std::vector<WAVHeader> headers;
public:
    size_t parseFileHeader(const std::string &fileName);

    WAVHeader &getWAVHeader(size_t id);
};