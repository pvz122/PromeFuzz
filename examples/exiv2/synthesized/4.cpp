// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::FileIo::open at basicio.cpp:527:13 in basicio.hpp
// Exiv2::strError at futils.cpp:244:13 in futils.hpp
// Exiv2::strError at futils.cpp:244:13 in futils.hpp
// Exiv2::FileIo::mmap at basicio.cpp:256:15 in basicio.hpp
// Exiv2::FileIo::size at basicio.cpp:506:16 in basicio.hpp
// Exiv2::FileIo::write at basicio.cpp:349:16 in basicio.hpp
// Exiv2::FileIo::close at basicio.cpp:547:13 in basicio.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/basicio.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/futils.hpp>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    // Initialize XMP parser
    Exiv2::XmpParser::initialize();

    // Create a dummy file and write the input data to it
    const std::string dummy_file = "./dummy_file";
    FILE* f = fopen(dummy_file.c_str(), "wb");
    if (!f) return 0;
    fwrite(Data, 1, Size, f);
    fclose(f);

    // Create FileIo instance
    Exiv2::FileIo fileIo(dummy_file);

    // Open the file
    if (fileIo.open("rb") != 0) {
        Exiv2::strError();
        return 0;
    }

    // Get error string (even if no error occurred)
    Exiv2::strError();

    // Memory map the file
    try {
        Exiv2::byte* mapped = fileIo.mmap(false);
        if (mapped) {
            // Get file size
            size_t fileSize = fileIo.size();

            // Write some data (just a small portion to avoid excessive writes)
            if (Size > 0) {
                size_t writeSize = Size > 1024 ? 1024 : Size;
                fileIo.write(Data, writeSize);
            }
        }
    } catch (...) {
        // Ignore exceptions
    }

    // Close the file
    fileIo.close();

    // Clean up the dummy file
    remove(dummy_file.c_str());

    return 0;
}