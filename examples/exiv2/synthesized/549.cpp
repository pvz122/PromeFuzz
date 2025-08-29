// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::getValue at value.hpp:1330:17 in value.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::f2Data at types.cpp:410:8 in types.hpp
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::Image::setByteOrder at image.cpp:677:13 in image.hpp
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <exiv2/exiv2.hpp>

extern "C" int LLVMFuzzerTestOneInput_549(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Initialize Exiv2
    Exiv2::XmpParser::initialize();
    ::atexit(Exiv2::XmpParser::terminate);

    try {
        // Test getValue with proper bounds checking
        Exiv2::ByteOrder byteOrder = static_cast<Exiv2::ByteOrder>(Data[0] % 3);
        if (Size >= 2) {
            uint16_t val = Exiv2::getValue<uint16_t>(Data, byteOrder);
        }

        // Test ValueType::copy with proper buffer size
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
        if (value.get()) {
            Exiv2::byte buf[2] = {0};
            value->copy(buf, byteOrder);
        }

        // Test f2Data with proper buffer size
        if (Size >= sizeof(float)) {
            float f = *reinterpret_cast<const float*>(Data);
            Exiv2::byte buf[4] = {0};
            Exiv2::f2Data(buf, f, byteOrder);
        }

        // Create a dummy file
        std::ofstream file("./dummy_file", std::ios::binary);
        if (file.is_open()) {
            file.write(reinterpret_cast<const char*>(Data), Size);
            file.close();

            // Test Image::setByteOrder
            Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
            if (image.get() != nullptr) {
                image->setByteOrder(byteOrder);
            }
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}