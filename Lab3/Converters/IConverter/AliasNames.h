#pragma once

#include <memory>

namespace Converter {
    class IConverter;
    using IConverterPtr = std::shared_ptr<IConverter>;
}