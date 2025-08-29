// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::IptcData::add at iptc.cpp:238:15 in iptc.hpp
// Exiv2::RafImage::setIptcData at rafimage.cpp:56:16 in rafimage.hpp
// Exiv2::CrwImage::setIptcData at crwimage.cpp:45:16 in crwimage.hpp
// Exiv2::MrwImage::setIptcData at mrwimage.cpp:46:16 in mrwimage.hpp
// Exiv2::WebPImage::setIptcData at webpimage.cpp:80:17 in webpimage.hpp
// Exiv2::GifImage::setIptcData at gifimage.cpp:27:16 in gifimage.hpp
// Exiv2::TgaImage::setIptcData at tgaimage.cpp:29:16 in tgaimage.hpp
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
#include <exiv2/tgaimage.hpp>
#include <exiv2/crwimage.hpp>
#include <exiv2/rafimage.hpp>
#include <exiv2/gifimage.hpp>
#include <exiv2/webpimage.hpp>
#include <exiv2/mrwimage.hpp>

#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_203(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file
    const std::string filename = "./dummy_file";
    std::ofstream out(filename, std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    try {
        // Create image objects
        auto rafIo = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(filename));
        Exiv2::RafImage rafImage(std::move(rafIo), false);

        auto crwIo = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(filename));
        Exiv2::CrwImage crwImage(std::move(crwIo), false);

        auto mrwIo = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(filename));
        Exiv2::MrwImage mrwImage(std::move(mrwIo), false);

        auto webpIo = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(filename));
        Exiv2::WebPImage webpImage(std::move(webpIo));

        auto gifIo = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(filename));
        Exiv2::GifImage gifImage(std::move(gifIo));

        auto tgaIo = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(filename));
        Exiv2::TgaImage tgaImage(std::move(tgaIo));

        // Create dummy IPTC data
        Exiv2::IptcKey key("Iptc.Application2.ObjectName");
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
        value->read("Test");
        Exiv2::Iptcdatum datum(key, value.get());
        Exiv2::IptcData iptcData;
        iptcData.add(datum);

        // Call setIptcData on each image type
        try { rafImage.setIptcData(iptcData); } catch (...) {}
        try { crwImage.setIptcData(iptcData); } catch (...) {}
        try { mrwImage.setIptcData(iptcData); } catch (...) {}
        try { webpImage.setIptcData(iptcData); } catch (...) {}
        try { gifImage.setIptcData(iptcData); } catch (...) {}
        try { tgaImage.setIptcData(iptcData); } catch (...) {}

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}