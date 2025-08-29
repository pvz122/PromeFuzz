// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::IptcData::empty at iptc.hpp:247:22 in iptc.hpp
// Exiv2::IptcData::begin at iptc.hpp:207:12 in iptc.hpp
// Exiv2::IptcData::end at iptc.hpp:211:12 in iptc.hpp
// Exiv2::IptcData::begin at iptc.hpp:207:12 in iptc.hpp
// Exiv2::IptcData::end at iptc.hpp:211:12 in iptc.hpp
// Exiv2::IptcData::findId at iptc.cpp:260:30 in iptc.hpp
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
#include <exiv2/image.hpp>
#include <cstdint>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_175(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file with the fuzzer input
    std::ofstream outFile("./dummy_file", std::ios::binary);
    if (!outFile) return 0;
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
        if (image.get() == 0) return 0;
        image->readMetadata();
        Exiv2::IptcData &iptcData = image->iptcData();

        // Test empty()
        bool isEmpty = iptcData.empty();

        // Test begin() and end()
        Exiv2::IptcData::const_iterator constItBegin = iptcData.begin();
        Exiv2::IptcData::const_iterator constItEnd = iptcData.end();
        Exiv2::IptcData::iterator itBegin = iptcData.begin();
        Exiv2::IptcData::iterator itEnd = iptcData.end();

        // Test findId()
        uint16_t dataset = static_cast<uint16_t>(Data[0]);
        Exiv2::IptcData::const_iterator foundIt = iptcData.findId(dataset);

        // Test erase() if not empty and iterator is valid
        if (!iptcData.empty() && itBegin != iptcData.end()) {
            Exiv2::IptcData::iterator nextIt = iptcData.erase(itBegin);
        }

    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}