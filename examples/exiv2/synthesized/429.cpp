// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::read at value.cpp:183:22 in value.hpp
// Exiv2::StringValueBase::toInt64 at value.cpp:209:26 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::toFloat at value.cpp:219:24 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::toUint32 at value.cpp:214:27 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::toRational at value.cpp:224:27 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::read at value.cpp:183:22 in value.hpp
// Exiv2::StringValueBase::toInt64 at value.cpp:209:26 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::toFloat at value.cpp:219:24 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::toUint32 at value.cpp:214:27 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::toRational at value.cpp:224:27 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::CommentValue::read at value.cpp:305:19 in value.hpp
// Exiv2::StringValueBase::toInt64 at value.cpp:209:26 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::toFloat at value.cpp:219:24 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::toUint32 at value.cpp:214:27 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::toRational at value.cpp:224:27 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
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
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_429(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a string from the input data
        std::string input(reinterpret_cast<const char*>(Data), Size);

        // Test with StringValue
        Exiv2::StringValue stringValue(input);
        stringValue.count();
        stringValue.read(Data, Size, Exiv2::invalidByteOrder);
        stringValue.toInt64(Size % (stringValue.count() + 1));
        stringValue.toFloat(Size % (stringValue.count() + 1));
        stringValue.toUint32(Size % (stringValue.count() + 1));
        stringValue.toRational(Size % (stringValue.count() + 1));

        // Test with AsciiValue
        Exiv2::AsciiValue asciiValue(input);
        asciiValue.count();
        asciiValue.read(Data, Size, Exiv2::invalidByteOrder);
        asciiValue.toInt64(Size % (asciiValue.count() + 1));
        asciiValue.toFloat(Size % (asciiValue.count() + 1));
        asciiValue.toUint32(Size % (asciiValue.count() + 1));
        asciiValue.toRational(Size % (asciiValue.count() + 1));

        // Test with CommentValue
        Exiv2::CommentValue commentValue(input);
        commentValue.count();
        commentValue.read(input);
        commentValue.toInt64(Size % (commentValue.count() + 1));
        commentValue.toFloat(Size % (commentValue.count() + 1));
        commentValue.toUint32(Size % (commentValue.count() + 1));
        commentValue.toRational(Size % (commentValue.count() + 1));

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}