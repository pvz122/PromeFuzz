// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::Photoshop::locateIptcIrb at photoshop.cpp:105:16 in photoshop.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::IptcParser::encode at iptc.cpp:422:21 in iptc.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::cmpBytes at types.cpp:164:21 in types.hpp
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
#include <vector>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a DataBuf with the input data
        Exiv2::DataBuf buf(Size);
        std::copy(Data, Data + Size, buf.data());

        // Call DataBuf::size()
        buf.size();

        // Call Photoshop::locateIptcIrb
        const Exiv2::byte* record = nullptr;
        uint32_t sizeHdr = 0;
        uint32_t sizeData = 0;
        Exiv2::Photoshop::locateIptcIrb(buf.data(), buf.size(), &record, sizeHdr, sizeData);

        // Call DataBuf::data()
        buf.data();

        // Call DataBuf::size() again
        buf.size();

        // Create an empty IptcData and call IptcParser::encode
        Exiv2::IptcData iptcData;
        Exiv2::DataBuf encoded = Exiv2::IptcParser::encode(iptcData);

        // Call DataBuf::size() on the encoded data
        encoded.size();

        // Call DataBuf::cmpBytes with a small buffer
        uint8_t cmpBuf[1] = {0};
        if (encoded.size() > 0) {
            encoded.cmpBytes(0, cmpBuf, 1);
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}