// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_tIME at pngset.c:1123:1 in png.h
// png_convert_to_rfc1123_buffer at png.c:737:1 in png.h
// png_get_tIME at pngget.c:1195:1 in png.h
// png_convert_from_time_t at pngwrite.c:521:1 in png.h
// png_convert_from_struct_tm at pngwrite.c:508:1 in png.h
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
#include <ctime>

extern "C" int LLVMFuzzerTestOneInput_115(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(png_time)) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    png_time mod_time;
    memcpy(&mod_time, Data, sizeof(png_time));

    png_set_tIME(png_ptr, info_ptr, &mod_time);

    char out[29];
    png_convert_to_rfc1123_buffer(out, &mod_time);

    png_timep retrieved_time;
    png_get_tIME(png_ptr, info_ptr, &retrieved_time);

    time_t ttime = time(nullptr);
    png_convert_from_time_t(&mod_time, ttime);

    struct tm tm_time;
    gmtime_r(&ttime, &tm_time);
    png_convert_from_struct_tm(&mod_time, &tm_time);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}