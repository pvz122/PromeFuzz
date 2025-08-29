// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_read_info at pngread.c:91:1 in png.h
// png_get_channels at pngget.c:481:1 in png.h
// png_get_filter_type at pngget.c:98:1 in png.h
// png_get_compression_type at pngget.c:116:1 in png.h
// png_get_color_type at pngget.c:89:1 in png.h
// png_get_interlace_type at pngget.c:107:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0; // PNG files start with an 8-byte header

    // Write the input data to a dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy file for reading
    file = fopen("./dummy_file", "rb");
    if (!file) return 0;

    // Initialize PNG structures
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) {
        fclose(file);
        return 0;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        fclose(file);
        return 0;
    }

    // Set up error handling
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        fclose(file);
        return 0;
    }

    // Read the PNG header
    png_init_io(png_ptr, file);
    png_read_info(png_ptr, info_ptr);

    // Call the target functions
    png_get_channels(png_ptr, info_ptr);
    png_get_filter_type(png_ptr, info_ptr);
    png_get_compression_type(png_ptr, info_ptr);
    png_get_color_type(png_ptr, info_ptr);
    png_get_interlace_type(png_ptr, info_ptr);

    // Clean up
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    fclose(file);

    return 0;
}