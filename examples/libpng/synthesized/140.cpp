// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_save_uint_32 at pngwutil.c:41:1 in png.h
// png_create_read_struct at pngread.c:24:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_get_uint_31 at pngrutil.c:41:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_get_palette_max at pngget.c:1360:1 in png.h
// png_chunk_warning at pngerror.c:497:1 in png.h
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
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_140(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Test png_save_uint_32
    png_byte buf[4];
    png_save_uint_32(buf, *reinterpret_cast<const png_uint_32*>(Data));

    // Test png_get_uint_32
    png_uint_32 val = png_get_uint_32(buf);

    // Test png_get_uint_31
    png_structp png_struct_instance = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_struct_instance) return 0;

    if (setjmp(png_jmpbuf(png_struct_instance))) {
        png_destroy_read_struct(&png_struct_instance, nullptr, nullptr);
        return 0;
    }

    png_uint_32 val31 = png_get_uint_31(png_struct_instance, buf);

    // Test png_get_palette_max
    png_infop info_instance = png_create_info_struct(png_struct_instance);
    if (!info_instance) {
        png_destroy_read_struct(&png_struct_instance, nullptr, nullptr);
        return 0;
    }
    int max_palette = png_get_palette_max(png_struct_instance, info_instance);

    // Test png_chunk_warning
    png_chunk_warning(png_struct_instance, "Test warning message");

    png_destroy_read_struct(&png_struct_instance, &info_instance, nullptr);

    return 0;
}