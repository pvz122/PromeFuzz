// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_get_eXIf_1 at pngget.c:903:1 in png.h
// png_set_eXIf at pngset.c:322:1 in png.h
// png_get_eXIf at pngget.c:893:1 in png.h
// png_set_eXIf_1 at pngset.c:331:1 in png.h
// png_set_cICP at pngset.c:136:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    png_uint_32 num_exif = 0;
    png_bytep exif = nullptr;

    // Fuzz png_get_eXIf_1
    png_get_eXIf_1(png_ptr, info_ptr, &num_exif, &exif);

    // Fuzz png_set_eXIf
    png_set_eXIf(png_ptr, info_ptr, exif);

    // Fuzz png_get_eXIf
    png_get_eXIf(png_ptr, info_ptr, &exif);

    // Fuzz png_set_eXIf_1
    png_set_eXIf_1(png_ptr, info_ptr, num_exif, exif);

    // Fuzz png_set_cICP
    png_byte colour_primaries = Data[0] % 256;
    png_byte transfer_function = Data[1] % 256;
    png_byte matrix_coefficients = Data[2] % 256;
    png_byte video_full_range_flag = Data[3] % 2;
    png_set_cICP(png_ptr, info_ptr, colour_primaries, transfer_function, matrix_coefficients, video_full_range_flag);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}