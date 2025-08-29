// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_get_error_ptr at pngerror.c:856:1 in png.h
// png_get_mem_ptr at pngmem.c:274:1 in png.h
// png_get_user_transform_ptr at pngtrans.c:836:1 in png.h
// png_get_user_chunk_ptr at pngget.c:1283:1 in png.h
// png_get_progressive_ptr at pngpread.c:930:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_voidp error_ptr = png_get_error_ptr(png_ptr);
    png_voidp mem_ptr = png_get_mem_ptr(png_ptr);
    png_voidp user_transform_ptr = png_get_user_transform_ptr(png_ptr);
    png_voidp user_chunk_ptr = png_get_user_chunk_ptr(png_ptr);
    png_voidp progressive_ptr = png_get_progressive_ptr(png_ptr);

    png_destroy_read_struct(&png_ptr, nullptr, nullptr);

    return 0;
}