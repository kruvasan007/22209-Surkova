#pragma once

#include "FactoryAliasNames.h"

#include <optional>

namespace Factory {

    struct IFactory {
        virtual ~IFactory() = default;

        template<typename Tag>
        typename Tag::InterfaceType create(Tag tag) {
            auto result_opt = createInstance(tag.id);
            if (!result_opt) return nullptr;
            typename Tag::InterfaceType *result = std::any_cast<typename Tag::InterfaceType>(&result_opt.value());
            if (result) {
                return *result;
            }
            return nullptr;
        }

    private:
        virtual std::optional<std::any> createInstance(const std::string &id) = 0;
    };

}