// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Photoshop::locateIrb at photoshop.cpp:34:16 in photoshop.hpp
// Exiv2::Photoshop::setIptcIrb at photoshop.cpp:115:20 in photoshop.hpp
// Exiv2::Photoshop::valid at photoshop.cpp:18:17 in photoshop.hpp
// Exiv2::Photoshop::locateIptcIrb at photoshop.cpp:105:16 in photoshop.hpp
// Exiv2::Photoshop::isIrb at photoshop.cpp:11:17 in photoshop.hpp
// Exiv2::Photoshop::locatePreviewIrb at photoshop.cpp:110:16 in photoshop.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/photoshop.hpp>
#include <exiv2/iptc.hpp>
#include <vector>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_264(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    const Exiv2::byte* pPsData = reinterpret_cast<const Exiv2::byte*>(Data);
    size_t sizePsData = Size;

    // Test locateIrb
    {
        const Exiv2::byte* record = nullptr;
        uint32_t sizeHdr = 0;
        uint32_t sizeData = 0;
        uint16_t psTag = 0x0404; // Arbitrary tag
        Exiv2::Photoshop::locateIrb(pPsData, sizePsData, psTag, &record, sizeHdr, sizeData);
    }

    // Test setIptcIrb
    {
        Exiv2::IptcData iptcData;
        Exiv2::DataBuf buf = Exiv2::Photoshop::setIptcIrb(pPsData, sizePsData, iptcData);
    }

    // Test valid
    {
        Exiv2::Photoshop::valid(pPsData, sizePsData);
    }

    // Test locateIptcIrb
    {
        const Exiv2::byte* record = nullptr;
        uint32_t sizeHdr = 0;
        uint32_t sizeData = 0;
        Exiv2::Photoshop::locateIptcIrb(pPsData, sizePsData, &record, sizeHdr, sizeData);
    }

    // Test isIrb
    {
        if (Size >= 4) {
            Exiv2::Photoshop::isIrb(pPsData);
        }
    }

    // Test locatePreviewIrb
    {
        const Exiv2::byte* record = nullptr;
        uint32_t sizeHdr = 0;
        uint32_t sizeData = 0;
        Exiv2::Photoshop::locatePreviewIrb(pPsData, sizePsData, &record, sizeHdr, sizeData);
    }

    return 0;
}