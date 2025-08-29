// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::Internal::MutableSliceBase::at at slice.hpp:174:15 in slice.hpp
// Exiv2::Internal::MutableSliceBase::at at slice.hpp:179:35 in slice.hpp
// Exiv2::ExifThumbC::writeFile at exif.cpp:379:20 in exif.hpp
// Exiv2::XmpTextValue::count at value.cpp:522:22 in value.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
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
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_481(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Exiv2
    Exiv2::XmpParser::initialize();
    ::atexit(Exiv2::XmpParser::terminate);

    // Test Exiv2::Internal::MutableSliceBase::at
    try {
        std::vector<uint8_t> vec(Data, Data + Size);
        if (!vec.empty()) {
            Exiv2::byte* data = vec.data();
            Exiv2::Slice<Exiv2::byte*> slice(data, 0, vec.size());
            slice.at(Size % vec.size());
            const auto& constSlice = slice;
            constSlice.at(Size % vec.size());
        }
    } catch (...) {
        // Ignore exceptions
    }

    // Test Exiv2::ExifThumbC::writeFile
    try {
        Exiv2::ExifData exifData;
        Exiv2::ExifThumb thumb(exifData);
        thumb.writeFile("./dummy_file");
    } catch (...) {
        // Ignore exceptions
    }

    // Test Exiv2::XmpTextValue::count
    try {
        Exiv2::XmpTextValue textValue;
        textValue.count();
    } catch (...) {
        // Ignore exceptions
    }

    // Test Exiv2::DataBuf::size
    try {
        Exiv2::DataBuf buf(Size % 1024);
        buf.size();
    } catch (...) {
        // Ignore exceptions
    }

    return 0;
}