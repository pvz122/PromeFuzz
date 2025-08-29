// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::IptcData::printStructure at iptc.cpp:278:16 in iptc.hpp
// Exiv2::IptcData::count at iptc.hpp:252:24 in iptc.hpp
// Exiv2::IptcData::begin at iptc.hpp:207:12 in iptc.hpp
// Exiv2::IptcData::end at iptc.hpp:211:12 in iptc.hpp
// Exiv2::IptcData::findId at iptc.cpp:260:30 in iptc.hpp
// Exiv2::IptcData::sortByTag at iptc.cpp:270:16 in iptc.hpp
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
#include <fstream>
#include <iostream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_510(const uint8_t *Data, size_t Size) {
    try {
        // Create dummy IPTC data
        Exiv2::IptcData iptcData;
        if (Size > 0) {
            Exiv2::byte* buffer = new Exiv2::byte[Size];
            std::memcpy(buffer, Data, Size);
            Exiv2::Slice<Exiv2::byte*> slice(buffer, 0, Size);

            // Test printStructure
            std::ofstream dummyOut("./dummy_file", std::ios::binary);
            Exiv2::IptcData::printStructure(dummyOut, slice, 0);
            dummyOut.close();

            delete[] buffer;
        }

        // Test count
        iptcData.count();

        // Test begin/end
        auto it_begin = iptcData.begin();
        auto it_end = iptcData.end();

        // Test findId with some arbitrary dataset and record
        if (Size > 2) {
            uint16_t dataset = static_cast<uint16_t>(Data[0]) | (static_cast<uint16_t>(Data[1]) << 8);
            uint16_t record = Exiv2::IptcDataSets::application2;
            iptcData.findId(dataset, record);
        }

        // Test sortByTag
        iptcData.sortByTag();

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}