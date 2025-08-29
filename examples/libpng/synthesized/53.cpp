// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_set_compression_level at pngwrite.c:1204:1 in png.h
// png_set_compression_mem_level at pngwrite.c:1215:1 in png.h
// png_set_compression_window_bits at pngwrite.c:1243:1 in png.h
// png_set_compression_strategy at pngwrite.c:1226:1 in png.h
// png_reset_zstream at png.c:974:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, nullptr);
        return 0;
    }

    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }

    png_init_io(png_ptr, fp);

    int level = Data[0] % 10;
    png_set_compression_level(png_ptr, level);

    int mem_level = Data[0] % 9 + 1;
    png_set_compression_mem_level(png_ptr, mem_level);

    int window_bits = Data[0] % 8 + 8;
    png_set_compression_window_bits(png_ptr, window_bits);

    int strategy = Data[0] % 4;
    png_set_compression_strategy(png_ptr, strategy);

    png_reset_zstream(png_ptr);

    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);

    return 0;
}