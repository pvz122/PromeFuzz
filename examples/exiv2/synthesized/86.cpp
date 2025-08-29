// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::XmpTextValue::count at value.cpp:522:22 in value.hpp
// Exiv2::DataValue::size at value.cpp:129:19 in value.hpp
// Exiv2::base64encode at futils.cpp:140:5 in futils.hpp
// Exiv2::Xmpdatum::count at xmp.cpp:348:18 in xmp_exiv2.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::base64decode at futils.cpp:168:8 in futils.hpp
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
#include <cstdint>
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Exiv2
    Exiv2::XmpParser::initialize();
    ::atexit(Exiv2::XmpParser::terminate);

    try {
        // Test Exiv2::XmpTextValue::count
        {
            std::string str(reinterpret_cast<const char*>(Data), std::min(Size, (size_t)1000));
            Exiv2::XmpTextValue value(str);
            value.count();
        }

        // Test Exiv2::DataValue::size
        {
            Exiv2::DataValue value(Data, std::min(Size, (size_t)1000));
            value.size();
        }

        // Test Exiv2::base64encode
        {
            size_t resultSize = ((std::min(Size, (size_t)1000) + 2) / 3) * 4 + 1;
            char* result = new char[resultSize];
            Exiv2::base64encode(Data, std::min(Size, (size_t)1000), result, resultSize);
            delete[] result;
        }

        // Test Exiv2::Xmpdatum::count
        {
            Exiv2::XmpKey key("Xmp.dc.title");
            Exiv2::Xmpdatum datum(key);
            datum.count();
        }

        // Test Exiv2::DataBuf::size
        {
            Exiv2::DataBuf buf(std::min(Size, (size_t)1000));
            if (Size > 0) {
                std::memcpy(buf.data(), Data, std::min(Size, (size_t)1000));
            }
            buf.size();
        }

        // Test Exiv2::base64decode
        {
            if (Size > 0) {
                std::string input(reinterpret_cast<const char*>(Data), std::min(Size, (size_t)1000));
                size_t outSize = input.length();
                char* out = new char[outSize];
                Exiv2::base64decode(input.c_str(), out, outSize);
                delete[] out;
            }
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}