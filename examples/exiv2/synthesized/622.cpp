// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Iptcdatum::setValue at iptc.cpp:201:16 in iptc.hpp
// Exiv2::IptcData::add at iptc.cpp:238:15 in iptc.hpp
// Exiv2::Iptcdatum::setValue at iptc.cpp:201:16 in iptc.hpp
// Exiv2::IptcData::add at iptc.cpp:238:15 in iptc.hpp
// Exiv2::IptcData::begin at iptc.hpp:207:12 in iptc.hpp
// Exiv2::IptcData::end at iptc.hpp:211:12 in iptc.hpp
// Exiv2::IptcData::findId at iptc.cpp:260:30 in iptc.hpp
// Exiv2::IptcData::sortByTag at iptc.cpp:270:16 in iptc.hpp
// Exiv2::IptcData::empty at iptc.hpp:247:22 in iptc.hpp
// Exiv2::IptcData::end at iptc.hpp:211:12 in iptc.hpp
// Exiv2::IptcData::erase at iptc.cpp:274:30 in iptc.hpp
// Exiv2::Iptcdatum::setValue at iptc.cpp:201:16 in iptc.hpp
// Exiv2::IptcData::add at iptc.cpp:238:15 in iptc.hpp
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
#include <vector>
#include <cstdint>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_622(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::IptcData iptcData;

        // Add some dummy data to work with
        Exiv2::IptcKey key1("Iptc.Application2.Headline");
        Exiv2::Iptcdatum datum1(key1);
        datum1.setValue("Test Headline");
        iptcData.add(datum1);

        Exiv2::IptcKey key2("Iptc.Application2.Caption");
        Exiv2::Iptcdatum datum2(key2);
        datum2.setValue("Test Caption");
        iptcData.add(datum2);

        // Test begin() and end()
        auto it_begin = iptcData.begin();
        auto it_end = iptcData.end();

        // Test findId()
        uint16_t dataset = Data[0] % 100;
        uint16_t record = Exiv2::IptcDataSets::application2;
        auto found_it = iptcData.findId(dataset, record);

        // Test sortByTag()
        iptcData.sortByTag();

        // Test erase() if not empty
        if (!iptcData.empty() && it_begin != iptcData.end()) {
            iptcData.erase(it_begin);
        }

        // Test add() with a new datum
        Exiv2::IptcKey key3("Iptc.Application2.Keywords");
        Exiv2::Iptcdatum datum3(key3);
        datum3.setValue("Fuzz");
        iptcData.add(datum3);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}