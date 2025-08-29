// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
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
#include <exiv2/exiv2.hpp>
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_535(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a dummy IPTC data file
        std::ofstream file("./dummy_file", std::ios::binary);
        file.write(reinterpret_cast<const char*>(Data), Size);
        file.close();

        // Read IPTC data from the file
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
        if (image.get() == nullptr) return 0;
        image->readMetadata();
        Exiv2::IptcData &iptcData = image->iptcData();

        // Test count()
        iptcData.count();

        // Test end()
        iptcData.end();

        // Test findId() with random dataset and record
        uint16_t dataset = Data[0] % 256;
        uint16_t record = Data[1] % 256;
        iptcData.findId(dataset, record);

        // Test erase() if data is not empty
        if (!iptcData.empty()) {
            auto it = iptcData.begin();
            iptcData.erase(it);
        }

        // Test size()
        iptcData.size();

        // Test begin()
        iptcData.begin();

    } catch (...) {
        // Handle all exceptions silently
    }

    return 0;
}