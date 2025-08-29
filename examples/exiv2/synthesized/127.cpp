// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::XmpData::add at xmp.cpp:435:14 in xmp_exiv2.hpp
// Exiv2::IptcData::add at iptc.cpp:238:15 in iptc.hpp
// Exiv2::copyIptcToXmp at convert.cpp:1355:6 in convert.hpp
// Exiv2::moveXmpToIptc at convert.cpp:1382:6 in convert.hpp
// Exiv2::moveIptcToXmp at convert.cpp:1366:6 in convert.hpp
// Exiv2::RafImage::setIptcData at rafimage.cpp:56:16 in rafimage.hpp
// Exiv2::Rw2Image::setIptcData at rw2image.cpp:52:16 in rw2image.hpp
// Exiv2::Rw2Image::writeMetadata at rw2image.cpp:182:16 in rw2image.hpp
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
#include <exiv2/convert.hpp>
#include <exiv2/rw2image.hpp>
#include <exiv2/rafimage.hpp>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_127(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create dummy file
        std::ofstream out("./dummy_file", std::ios::binary);
        out.write(reinterpret_cast<const char*>(Data), Size);
        out.close();

        // Initialize basic objects
        Exiv2::IptcData iptcData;
        Exiv2::XmpData xmpData;
        Exiv2::XmpKey xmpKey("Xmp.dc.title");
        Exiv2::IptcKey iptcKey("Iptc.Application2.ObjectName");
        Exiv2::Value::UniquePtr xmpValue = Exiv2::Value::create(Exiv2::xmpText);
        Exiv2::Value::UniquePtr iptcValue = Exiv2::Value::create(Exiv2::string);
        xmpValue->read("Test");
        iptcValue->read("Test");
        Exiv2::Xmpdatum xmpDatum(xmpKey, xmpValue.get());
        Exiv2::Iptcdatum iptcDatum(iptcKey, iptcValue.get());
        xmpData.add(xmpDatum);
        iptcData.add(iptcDatum);

        // Test copyIptcToXmp
        Exiv2::copyIptcToXmp(iptcData, xmpData);

        // Test moveXmpToIptc
        Exiv2::moveXmpToIptc(xmpData, iptcData);

        // Test moveIptcToXmp
        Exiv2::moveIptcToXmp(iptcData, xmpData);

        // Test RafImage::setIptcData
        auto rafIo = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
        Exiv2::RafImage rafImage(std::move(rafIo), false);
        try {
            rafImage.setIptcData(iptcData);
        } catch (const Exiv2::Error&) {}

        // Test Rw2Image::setIptcData
        auto rw2Io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
        Exiv2::Rw2Image rw2Image(std::move(rw2Io));
        try {
            rw2Image.setIptcData(iptcData);
        } catch (const Exiv2::Error&) {}

        // Test Rw2Image::writeMetadata
        try {
            rw2Image.writeMetadata();
        } catch (const Exiv2::Error&) {}

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}