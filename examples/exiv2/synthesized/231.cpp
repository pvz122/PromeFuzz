// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::StringValueBase::size at value.cpp:201:25 in value.hpp
// Exiv2::CommentValue::copy at value.cpp:340:22 in value.hpp
// Exiv2::CommentValue::copy at value.cpp:340:22 in value.hpp
// Exiv2::CommentValue::write at value.cpp:357:29 in value.hpp
// Exiv2::CommentValue::comment at value.cpp:366:27 in value.hpp
// Exiv2::CommentValue::comment at value.cpp:366:27 in value.hpp
// Exiv2::CommentValue::read at value.cpp:305:19 in value.hpp
// Exiv2::CommentValue::read at value.cpp:335:19 in value.hpp
// Exiv2::CommentValue::read at value.cpp:335:19 in value.hpp
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
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_231(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        std::string input(reinterpret_cast<const char*>(Data), Size);
        Exiv2::CommentValue commentValue(input);

        size_t bufSize = commentValue.size();
        if (bufSize > 0) {
            std::vector<Exiv2::byte> buf(bufSize);
            commentValue.copy(buf.data(), Exiv2::littleEndian);
            commentValue.copy(buf.data(), Exiv2::bigEndian);
        }

        std::ostringstream os;
        commentValue.write(os);

        commentValue.comment();
        commentValue.comment("UTF-8");

        commentValue.read(input);
        commentValue.read(Data, Size, Exiv2::littleEndian);
        commentValue.read(Data, Size, Exiv2::bigEndian);

        auto cloned = commentValue.clone();

    } catch (...) {
        // Ignore exceptions
    }

    return 0;
}