// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::IptcData::size at iptc.cpp:219:18 in iptc.hpp
// Exiv2::IptcData::size at iptc.cpp:219:18 in iptc.hpp
// Exiv2::Photoshop::setIptcIrb at photoshop.cpp:115:20 in photoshop.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/types.hpp>
#include <exiv2/photoshop.hpp>
#include <exiv2/iptc.hpp>

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize DataBuf with fuzzer input
    Exiv2::DataBuf buf(Size);
    std::memcpy(buf.data(), Data, Size);

    // Initialize IptcData
    Exiv2::IptcData iptcData;

    // Call size() functions
    (void)buf.size();
    (void)iptcData.size();
    (void)iptcData.size();

    // Call setIptcIrb
    Exiv2::DataBuf result = Exiv2::Photoshop::setIptcIrb(buf.data(), buf.size(), iptcData);
    (void)result.size();

    return 0;
}