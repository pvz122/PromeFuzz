// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::StringValueBase::size at value.cpp:201:25 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::read at value.cpp:183:22 in value.hpp
// Exiv2::StringValueBase::toInt64 at value.cpp:209:26 in value.hpp
// Exiv2::StringValueBase::toInt64 at value.cpp:209:26 in value.hpp
// Exiv2::StringValueBase::toUint32 at value.cpp:214:27 in value.hpp
// Exiv2::StringValueBase::toUint32 at value.cpp:214:27 in value.hpp
// Exiv2::StringValueBase::copy at value.cpp:190:25 in value.hpp
// Exiv2::StringValueBase::read at value.cpp:183:22 in value.hpp
// Exiv2::StringValueBase::size at value.cpp:201:25 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::toInt64 at value.cpp:209:26 in value.hpp
// Exiv2::StringValueBase::toUint32 at value.cpp:214:27 in value.hpp
// Exiv2::StringValueBase::copy at value.cpp:190:25 in value.hpp
// Exiv2::CommentValue::read at value.cpp:305:19 in value.hpp
// Exiv2::StringValueBase::size at value.cpp:201:25 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::toInt64 at value.cpp:209:26 in value.hpp
// Exiv2::StringValueBase::toUint32 at value.cpp:214:27 in value.hpp
// Exiv2::CommentValue::copy at value.cpp:340:22 in value.hpp
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
#include <cstring>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_179(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a string from the input data
    std::string input(reinterpret_cast<const char*>(Data), Size);

    try {
        // Test with StringValue
        Exiv2::StringValue stringValue(input);
        
        // Call size()
        size_t strSize = stringValue.size();
        
        // Call count()
        (void)stringValue.count();
        
        // Call read()
        std::vector<Exiv2::byte> buf(Size);
        if (Size > 0) {
            std::memcpy(buf.data(), Data, Size);
            (void)stringValue.read(buf.data(), Size, Exiv2::invalidByteOrder);
        }
        
        // Call toInt64()
        if (strSize > 0) {
            (void)stringValue.toInt64(0);
            if (strSize > 1) {
                (void)stringValue.toInt64(strSize - 1);
            }
        }
        
        // Call toUint32()
        if (strSize > 0) {
            (void)stringValue.toUint32(0);
            if (strSize > 1) {
                (void)stringValue.toUint32(strSize - 1);
            }
        }
        
        // Call copy()
        if (strSize > 0) {
            std::vector<Exiv2::byte> outBuf(strSize);
            (void)stringValue.copy(outBuf.data(), Exiv2::invalidByteOrder);
        }

        // Test with AsciiValue
        Exiv2::AsciiValue asciiValue;
        if (Size > 0) {
            (void)asciiValue.read(Data, Size, Exiv2::invalidByteOrder);
            size_t asciiSize = asciiValue.size();
            (void)asciiValue.count();
            if (asciiSize > 0) {
                (void)asciiValue.toInt64(0);
                (void)asciiValue.toUint32(0);
            }
            if (asciiSize > 0) {
                std::vector<Exiv2::byte> asciiBuf(asciiSize);
                (void)asciiValue.copy(asciiBuf.data(), Exiv2::invalidByteOrder);
            }
        }

        // Test with CommentValue
        Exiv2::CommentValue commentValue;
        if (Size > 0) {
            std::string commentStr(input);
            (void)commentValue.read(commentStr);
            size_t commentSize = commentValue.size();
            (void)commentValue.count();
            if (commentSize > 0) {
                (void)commentValue.toInt64(0);
                (void)commentValue.toUint32(0);
            }
            if (commentSize > 0) {
                std::vector<Exiv2::byte> commentBuf(commentSize);
                (void)commentValue.copy(commentBuf.data(), Exiv2::invalidByteOrder);
            }
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}