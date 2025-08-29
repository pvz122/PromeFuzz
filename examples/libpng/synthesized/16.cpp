// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_get_libpng_ver at png.c:837:1 in png.h
// png_get_copyright at png.c:811:1 in png.h
// png_warning at pngerror.c:216:1 in png.h
// png_benign_error at pngerror.c:362:1 in png.h
// png_get_header_ver at png.c:844:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <png.h>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    // Test png_get_libpng_ver
    const char* version = png_get_libpng_ver(png_ptr);

    // Test png_get_copyright
    const char* copyright = png_get_copyright(png_ptr);

    // Test png_warning
    char warning_message[256];
    if (Size > 255) Size = 255;
    memcpy(warning_message, Data, Size);
    warning_message[Size] = '\0';
    png_warning(png_ptr, warning_message);

    // Test png_benign_error
    png_benign_error(png_ptr, warning_message);

    // Test png_get_header_ver
    const char* header_ver = png_get_header_ver(png_ptr);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}