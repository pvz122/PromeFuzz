// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::IptcKey::record at datasets.cpp:538:19 in datasets.hpp
// Exiv2::IptcKey::tag at datasets.cpp:530:19 in datasets.hpp
// Exiv2::IptcData::add at iptc.cpp:238:15 in iptc.hpp
// Exiv2::IptcData::findKey at iptc.cpp:252:30 in iptc.hpp
// Exiv2::IptcData::end at iptc.hpp:211:12 in iptc.hpp
// Exiv2::Iptcdatum::record at iptc.cpp:84:21 in iptc.hpp
// Exiv2::Iptcdatum::tag at iptc.cpp:108:21 in iptc.hpp
// Exiv2::IptcDataSets::dataSetType at datasets.cpp:404:22 in datasets.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/datasets.hpp>
#include <exiv2/iptc.hpp>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Create IptcKey
    uint16_t tag = *reinterpret_cast<const uint16_t*>(Data);
    uint16_t record = *reinterpret_cast<const uint16_t*>(Data + 2);
    Exiv2::IptcKey key(tag, record);

    // Test IptcKey::record()
    (void)key.record();

    // Test IptcKey::tag()
    (void)key.tag();

    // Create IptcData
    Exiv2::IptcData iptcData;
    Exiv2::Iptcdatum datum(key);
    iptcData.add(datum);

    // Test IptcData::findKey()
    auto it = iptcData.findKey(key);
    if (it != iptcData.end()) {
        // Test Iptcdatum::record()
        (void)it->record();

        // Test Iptcdatum::tag()
        (void)it->tag();
    }

    // Test IptcDataSets::dataSetType()
    (void)Exiv2::IptcDataSets::dataSetType(tag, record);

    return 0;
}