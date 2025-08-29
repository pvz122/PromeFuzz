// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_cLLI at pngset.c:194:1 in png.h
// png_set_cHRM at pngset.c:99:1 in png.h
// png_set_mDCV at pngset.c:297:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < 96) return 0; // Ensure enough data for all double values

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }

    // Extract values from the input data
    double maxCLL = 0.0, maxFALL = 0.0;
    double white_x = 0.0, white_y = 0.0;
    double red_x = 0.0, red_y = 0.0;
    double green_x = 0.0, green_y = 0.0;
    double blue_x = 0.0, blue_y = 0.0;
    double mastering_display_max_luminance = 0.0, mastering_display_min_luminance = 0.0;

    if (Size >= 8) maxCLL = *reinterpret_cast<const double*>(Data);
    if (Size >= 16) maxFALL = *reinterpret_cast<const double*>(Data + 8);
    if (Size >= 24) white_x = *reinterpret_cast<const double*>(Data + 16);
    if (Size >= 32) white_y = *reinterpret_cast<const double*>(Data + 24);
    if (Size >= 40) red_x = *reinterpret_cast<const double*>(Data + 32);
    if (Size >= 48) red_y = *reinterpret_cast<const double*>(Data + 40);
    if (Size >= 56) green_x = *reinterpret_cast<const double*>(Data + 48);
    if (Size >= 64) green_y = *reinterpret_cast<const double*>(Data + 56);
    if (Size >= 72) blue_x = *reinterpret_cast<const double*>(Data + 64);
    if (Size >= 80) blue_y = *reinterpret_cast<const double*>(Data + 72);
    if (Size >= 88) mastering_display_max_luminance = *reinterpret_cast<const double*>(Data + 80);
    if (Size >= 96) mastering_display_min_luminance = *reinterpret_cast<const double*>(Data + 88);

    // Call the target functions
    png_set_cLLI(png_ptr, info_ptr, maxCLL, maxFALL);
    png_set_cHRM(png_ptr, info_ptr, white_x, white_y, red_x, red_y, green_x, green_y, blue_x, blue_y);
    png_set_mDCV(png_ptr, info_ptr, white_x, white_y, red_x, red_y, green_x, green_y, blue_x, blue_y, mastering_display_max_luminance, mastering_display_min_luminance);

    // Cleanup
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}