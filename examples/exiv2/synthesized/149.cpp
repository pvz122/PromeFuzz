// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::CrwImage::setIptcData at crwimage.cpp:45:16 in crwimage.hpp
// Exiv2::MrwImage::setIptcData at mrwimage.cpp:46:16 in mrwimage.hpp
// Exiv2::BmffImage::setIptcData at bmffimage.cpp:697:17 in bmffimage.hpp
// Exiv2::GifImage::setIptcData at gifimage.cpp:27:16 in gifimage.hpp
// Exiv2::TgaImage::setIptcData at tgaimage.cpp:29:16 in tgaimage.hpp
// Exiv2::BmpImage::setIptcData at bmpimage.cpp:34:16 in bmpimage.hpp
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
#include <exiv2/bmffimage.hpp>
#include <exiv2/gifimage.hpp>
#include <exiv2/bmpimage.hpp>
#include <exiv2/mrwimage.hpp>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <vector>

static void createDummyFile(const uint8_t *data, size_t size) {
    std::ofstream out("./dummy_file", std::ios::binary);
    out.write(reinterpret_cast<const char*>(data), size);
    out.close();
}

extern "C" int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    createDummyFile(data, size);

    try {
        auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
        Exiv2::IptcData iptcData;

        switch (data[0] % 6) {
            case 0: {
                Exiv2::CrwImage crwImage(std::move(io), false);
                crwImage.setIptcData(iptcData);
                break;
            }
            case 1: {
                Exiv2::MrwImage mrwImage(std::move(io), false);
                mrwImage.setIptcData(iptcData);
                break;
            }
            case 2: {
                Exiv2::BmffImage bmffImage(std::move(io), false);
                bmffImage.setIptcData(iptcData);
                break;
            }
            case 3: {
                Exiv2::GifImage gifImage(std::move(io));
                gifImage.setIptcData(iptcData);
                break;
            }
            case 4: {
                Exiv2::TgaImage tgaImage(std::move(io));
                tgaImage.setIptcData(iptcData);
                break;
            }
            case 5: {
                Exiv2::BmpImage bmpImage(std::move(io));
                bmpImage.setIptcData(iptcData);
                break;
            }
        }
    } catch (const Exiv2::Error&) {
        // Expected exceptions, ignore
    }

    return 0;
}