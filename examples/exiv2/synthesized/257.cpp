// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::IptcData::findKey at iptc.cpp:252:30 in iptc.hpp
// Exiv2::IptcData::findKey at iptc.cpp:248:36 in iptc.hpp
// Exiv2::IptcData::findId at iptc.cpp:260:30 in iptc.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::IptcData::add at iptc.cpp:234:15 in iptc.hpp
// Exiv2::IptcData::begin at iptc.hpp:207:12 in iptc.hpp
// Exiv2::IptcData::empty at iptc.hpp:247:22 in iptc.hpp
// Exiv2::IptcData::end at iptc.hpp:211:12 in iptc.hpp
// Exiv2::IptcData::erase at iptc.cpp:274:30 in iptc.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/iptc.hpp>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_257(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    try {
        Exiv2::IptcData iptcData;

        // Create a dummy IptcKey
        std::string keyStr = "Iptc.Application2.Headline";
        Exiv2::IptcKey key(keyStr);

        // Test findKey (both const and non-const versions)
        auto it1 = iptcData.findKey(key);
        const auto& constIptcData = iptcData;
        auto it2 = constIptcData.findKey(key);

        // Test findId
        uint16_t dataset = Data[0] % 256;
        uint16_t record = Exiv2::IptcDataSets::application2;
        auto it3 = iptcData.findId(dataset, record);

        // Test add
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
        value->read("Test Value");
        iptcData.add(key, value.get());

        // Test begin
        auto it_begin = iptcData.begin();

        // Test erase (only if container is not empty)
        if (!iptcData.empty() && it_begin != iptcData.end()) {
            iptcData.erase(it_begin);
        }

    } catch (...) {
        // Catch all exceptions silently
    }

    return 0;
}