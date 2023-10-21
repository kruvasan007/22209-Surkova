#include <Tags.h>
#include <IConverter/AliasNames.h>
#include <MuteConverter.h>
#include "include/AliasNames.h"
#include <MixConverter.h>
#include <FlexConverter.h>

namespace Converter {
    Factory::FactoryMap getFactoryItemsMap() {
        Factory::FactoryMap factoryMap;
        factoryMap.insert({muteConverterTag.id,
                           []() {
                               return std::make_any<IConverterPtr>(
                                       std::make_shared<MuteConverter>());
                           }});
        factoryMap.insert({mixConverterTag.id,
                           []() {
                               return std::make_any<IConverterPtr>(
                                       std::make_shared<MixConverter>());
                           }});
        factoryMap.insert({flexConverterTag.id,
                           []() {
                               return std::make_any<IConverterPtr>(
                                       std::make_shared<FlexConverter>());
                           }});
        return factoryMap;
    }
}
