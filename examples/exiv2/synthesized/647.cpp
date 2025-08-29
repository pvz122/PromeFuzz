// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::IptcData::add at iptc.cpp:234:15 in iptc.hpp
// Exiv2::IptcData::count at iptc.hpp:252:24 in iptc.hpp
// Exiv2::IptcData::end at iptc.hpp:211:12 in iptc.hpp
// Exiv2::IptcData::findId at iptc.cpp:260:30 in iptc.hpp
// Exiv2::IptcData::empty at iptc.hpp:247:22 in iptc.hpp
// Exiv2::IptcData::begin at iptc.hpp:207:12 in iptc.hpp
// Exiv2::IptcData::erase at iptc.cpp:274:30 in iptc.hpp
// Exiv2::IptcData::size at iptc.cpp:219:18 in iptc.hpp
// Exiv2::IptcData::begin at iptc.hpp:207:12 in iptc.hpp
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

extern "C" int LLVMFuzzerTestOneInput_647(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::IptcData iptcData;

        // Add some dummy data to the IptcData object
        Exiv2::IptcKey key("Iptc.Application2.Headline");
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
        value->read("Test");
        iptcData.add(key, value.get());

        // Test count()
        iptcData.count();

        // Test end()
        iptcData.end();

        // Test findId()
        uint16_t dataset = Data[0] % 100;
        uint16_t record = Exiv2::IptcDataSets::application2;
        iptcData.findId(dataset, record);

        // Test erase()
        if (!iptcData.empty()) {
            auto it = iptcData.begin();
            iptcData.erase(it);
        }

        // Test size()
        iptcData.size();

        // Test begin()
        iptcData.begin();

    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}