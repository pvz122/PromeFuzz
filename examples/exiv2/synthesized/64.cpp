// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::CommentValue::CharsetInfo::name at value.cpp:276:40 in value.hpp
// Exiv2::CommentValue::CharsetInfo::charsetIdByCode at value.cpp:291:52 in value.hpp
// Exiv2::CommentValue::CharsetInfo::code at value.cpp:280:40 in value.hpp
// Exiv2::CommentValue::CharsetInfo::charsetIdByName at value.cpp:284:52 in value.hpp
// Exiv2::CommentValue::detectCharset at value.cpp:396:27 in value.hpp
// Exiv2::CommentValue::charsetId at value.cpp:387:39 in value.hpp
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
#include <string>

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test Exiv2::CommentValue::CharsetInfo::name
    Exiv2::CommentValue::CharsetId charsetId = static_cast<Exiv2::CommentValue::CharsetId>(Data[0] % Exiv2::CommentValue::lastCharsetId);
    const char* charsetName = Exiv2::CommentValue::CharsetInfo::name(charsetId);
    (void)charsetName; // Avoid unused variable warning

    // Test Exiv2::CommentValue::CharsetInfo::charsetIdByCode
    std::string code(reinterpret_cast<const char*>(Data), Size);
    Exiv2::CommentValue::CharsetId idByCode = Exiv2::CommentValue::CharsetInfo::charsetIdByCode(code);
    (void)idByCode;

    // Test Exiv2::CommentValue::CharsetInfo::code
    const char* charsetCode = Exiv2::CommentValue::CharsetInfo::code(charsetId);
    (void)charsetCode;

    // Test Exiv2::CommentValue::CharsetInfo::charsetIdByName
    std::string name(reinterpret_cast<const char*>(Data), Size);
    Exiv2::CommentValue::CharsetId idByName = Exiv2::CommentValue::CharsetInfo::charsetIdByName(name);
    (void)idByName;

    // Test Exiv2::CommentValue::detectCharset and charsetId
    std::string comment(reinterpret_cast<const char*>(Data), Size);
    Exiv2::CommentValue commentValue(comment);
    const char* detectedCharset = commentValue.detectCharset(comment);
    (void)detectedCharset;
    Exiv2::CommentValue::CharsetId commentCharsetId = commentValue.charsetId();
    (void)commentCharsetId;

    return 0;
}