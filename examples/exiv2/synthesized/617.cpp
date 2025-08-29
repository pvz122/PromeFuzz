// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::IptcData::add at iptc.cpp:234:15 in iptc.hpp
// Exiv2::IptcData::begin at iptc.hpp:207:12 in iptc.hpp
// Exiv2::IptcData::end at iptc.hpp:211:12 in iptc.hpp
// Exiv2::IptcData::findId at iptc.cpp:260:30 in iptc.hpp
// Exiv2::IptcData::empty at iptc.hpp:247:22 in iptc.hpp
// Exiv2::IptcData::end at iptc.hpp:211:12 in iptc.hpp
// Exiv2::IptcData::erase at iptc.cpp:274:30 in iptc.hpp
// Exiv2::IptcData::sortByTag at iptc.cpp:270:16 in iptc.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::IptcData::add at iptc.cpp:234:15 in iptc.hpp
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
#include <vector>
#include <algorithm>

extern "C" int LLVMFuzzerTestOneInput_617(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::IptcData iptcData;

        // Add some dummy data to the IptcData
        Exiv2::IptcKey key("Iptc.Application2.Headline");
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
        value->read("Test Value");
        iptcData.add(key, value.get());

        // Test begin() and end()
        auto it_begin = iptcData.begin();
        auto it_end = iptcData.end();

        // Test findId()
        uint16_t dataset = static_cast<uint16_t>(Data[0] % 0xFFFF);
        uint16_t record = Exiv2::IptcDataSets::application2;
        auto it_find = iptcData.findId(dataset, record);

        // Test erase() if the container is not empty
        if (!iptcData.empty() && it_begin != iptcData.end()) {
            iptcData.erase(it_begin);
        }

        // Test sortByTag()
        iptcData.sortByTag();

        // Test add() with valid dataset
        if (Size > 2) {
            uint16_t randomDataset = static_cast<uint16_t>((Data[1] << 8) | Data[2]) % 0xFFFF;
            try {
                Exiv2::IptcKey randomKey("Iptc.Application2.Headline");
                Exiv2::Value::UniquePtr randomValue = Exiv2::Value::create(Exiv2::asciiString);
                randomValue->read("Random Value");
                iptcData.add(randomKey, randomValue.get());
            } catch (...) {
                // Ignore invalid key exceptions
            }
        }
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}