// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_set_sRGB_gAMA_and_cHRM at pngset.c:836:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_set_iCCP at pngset.c:864:1 in png.h
// png_set_oFFs at pngset.c:470:1 in png.h
// png_set_unknown_chunk_location at pngset.c:1459:1 in png.h
// png_set_invalid at pngset.c:1791:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0;

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, nullptr);
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }

    // Fuzz png_set_sRGB_gAMA_and_cHRM
    png_set_sRGB_gAMA_and_cHRM(png_ptr, info_ptr, Data[0] % 4);

    // Fuzz png_set_iCCP
    const char *name = "dummy_profile";
    int compression_type = Data[0] % 2;
    if (compression_type != PNG_COMPRESSION_TYPE_BASE) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }
    png_set_iCCP(png_ptr, info_ptr, name, compression_type, Data, Size);

    // Fuzz png_set_oFFs
    png_int_32 offset_x = static_cast<png_int_32>(Data[0]);
    png_int_32 offset_y = static_cast<png_int_32>(Data[1]);
    int unit_type = Data[2] % 2;
    png_set_oFFs(png_ptr, info_ptr, offset_x, offset_y, unit_type);

    // Fuzz png_set_unknown_chunk_location
    int chunk = Data[3] % 10;
    int location = Data[4] % 3;
    png_set_unknown_chunk_location(png_ptr, info_ptr, chunk, location);

    // Fuzz png_set_invalid
    int mask = Data[5] % 256;
    png_set_invalid(png_ptr, info_ptr, mask);

    png_destroy_write_struct(&png_ptr, &info_ptr);
    return 0;
}