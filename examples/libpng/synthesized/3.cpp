// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_sig_bytes at png.c:53:1 in png.h
// png_set_crc_action at pngrtran.c:35:1 in png.h
// png_set_read_fn at pngrio.c:86:1 in png.h
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
#include <cstdio>
#include <cstdlib>

static void dummy_read_data(png_structp png_ptr, png_bytep data, png_size_t length) {
    // Dummy read function
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < 3) return 0; // Ensure there are at least 3 bytes of input data

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    int num_bytes = Data[0] % 9; // Ensure num_bytes is between 0 and 8
    png_set_sig_bytes(png_ptr, num_bytes);

    int crit_action = Data[1] % 5; // Ensure crit_action is between 0 and 4
    int ancil_action = Data[2] % 5; // Ensure ancil_action is between 0 and 4
    png_set_crc_action(png_ptr, crit_action, ancil_action);

    png_set_read_fn(png_ptr, nullptr, dummy_read_data);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}