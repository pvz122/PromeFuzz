// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::AsciiValue::clone at value.hpp:437:13 in value.hpp
// Exiv2::IptcKey::clone at datasets.cpp:542:29 in datasets.hpp
// Exiv2::StringValue::clone at value.hpp:394:13 in value.hpp
// Exiv2::StringValue::clone at value.hpp:394:13 in value.hpp
// Exiv2::DateValue::clone at value.hpp:939:13 in value.hpp
// Exiv2::CommentValue::clone at value.hpp:520:13 in value.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/value.hpp>
#include <exiv2/metadatum.hpp>
#include <exiv2/iptc.hpp>
#include <memory>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_393(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Test Exiv2::AsciiValue::clone
        {
            Exiv2::AsciiValue value1;
            auto clone1 = value1.clone();
        }

        // Test Exiv2::Key::clone
        {
            Exiv2::IptcKey key("Iptc.Application2.Headline");
            auto clone2 = key.clone();
        }

        // Test Exiv2::StringValue::clone
        {
            std::string str(reinterpret_cast<const char*>(Data), Size);
            Exiv2::StringValue value2(str);
            auto clone3 = value2.clone();
        }

        // Test Exiv2::StringValueBase::clone
        {
            std::string str(reinterpret_cast<const char*>(Data), Size);
            Exiv2::StringValue value3(str);
            auto clone4 = value3.clone();
        }

        // Test Exiv2::DateValue::clone
        {
            Exiv2::DateValue value4;
            auto clone5 = value4.clone();
        }

        // Test Exiv2::CommentValue::clone
        {
            Exiv2::CommentValue value5;
            auto clone6 = value5.clone();
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}