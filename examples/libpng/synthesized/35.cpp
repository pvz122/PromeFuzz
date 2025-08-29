// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_write_chunk_data at pngwutil.c:144:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_set_rgb_to_gray_fixed at pngrtran.c:1024:1 in png.h
// png_set_benign_errors at pngset.c:1858:1 in png.h
// png_longjmp at pngerror.c:757:1 in png.h
// png_set_check_for_invalid_index at pngset.c:1888:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < 3) return 0;

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, nullptr);
        return 0;
    }

    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }

    png_init_io(png_ptr, file);

    // Fuzz png_write_chunk_data
    if (Size > 0) {
        png_write_chunk_data(png_ptr, Data, Size);
    }

    // Fuzz png_set_rgb_to_gray_fixed
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(file);
        return 0;
    }
    png_set_rgb_to_gray_fixed(png_ptr, Data[0] % 3, static_cast<png_fixed_point>(Data[1] * 100000), static_cast<png_fixed_point>(Data[2] * 100000));

    // Fuzz png_set_benign_errors
    if (Size > 3) {
        png_set_benign_errors(png_ptr, Data[3] % 2);
    }

    // Fuzz png_longjmp
    if (Size > 4 && Data[4] % 2) {
        png_longjmp(png_ptr, 1);
    }

    // Fuzz png_set_check_for_invalid_index
    if (Size > 5) {
        png_set_check_for_invalid_index(png_ptr, Data[5] % 2 == 0 ? 1 : -1);
    }

    fclose(file);
    png_destroy_write_struct(&png_ptr, &info_ptr);

    return 0;
}