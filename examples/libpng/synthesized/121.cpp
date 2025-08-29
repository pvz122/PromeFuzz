// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_save_uint_32 at pngwutil.c:41:1 in png.h
// png_create_read_struct at pngread.c:24:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_get_uint_31 at pngrutil.c:41:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_chunk_warning at pngerror.c:497:1 in png.h
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_info_struct at png.c:394:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_get_sPLT at pngget.c:746:1 in png.h
// png_destroy_info_struct at png.c:394:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Test png_save_uint_32
    png_byte buf[4];
    png_uint_32 value = *reinterpret_cast<const png_uint_32*>(Data);
    png_save_uint_32(buf, value);

    // Test png_get_uint_32
    png_uint_32 retrieved_value = png_get_uint_32(buf);

    // Test png_get_uint_31
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (png_ptr) {
        if (setjmp(png_jmpbuf(png_ptr))) {
            png_destroy_read_struct(&png_ptr, nullptr, nullptr);
            return 0;
        }
        png_uint_32 png_uint_31_value = png_get_uint_31(png_ptr, buf);
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
    }

    // Test png_chunk_warning
    png_chunk_warning(nullptr, "Test warning message");

    // Test png_get_sPLT
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr) {
        if (setjmp(png_jmpbuf(png_ptr))) {
            png_destroy_info_struct(png_ptr, &info_ptr);
            png_destroy_read_struct(&png_ptr, nullptr, nullptr);
            return 0;
        }
        png_sPLT_tpp entries = nullptr;
        int num_palettes = png_get_sPLT(png_ptr, info_ptr, entries);
        png_destroy_info_struct(png_ptr, &info_ptr);
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
    }

    return 0;
}