// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_start_read_image at pngread.c:201:1 in png.h
// png_get_rowbytes at pngget.c:40:1 in png.h
// png_get_rowbytes at pngget.c:40:1 in png.h
// png_read_rows at pngread.c:552:1 in png.h
// png_get_image_height at pngget.c:71:1 in png.h
// png_get_image_height at pngget.c:71:1 in png.h
// png_get_rowbytes at pngget.c:40:1 in png.h
// png_read_image at pngread.c:607:1 in png.h
// png_progressive_combine_row at pngpread.c:899:1 in png.h
// png_get_image_height at pngget.c:71:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize PNG structures
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    // Set up error handling
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }

    // Write input data to a dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Read the dummy file
    file = fopen("./dummy_file", "rb");
    if (!file) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }
    png_init_io(png_ptr, file);

    // Start reading the image
    png_start_read_image(png_ptr);

    // Allocate memory for rows
    png_bytep row = (png_bytep)malloc(png_get_rowbytes(png_ptr, info_ptr));
    png_bytep display_row = (png_bytep)malloc(png_get_rowbytes(png_ptr, info_ptr));

    // Read rows
    png_read_rows(png_ptr, &row, &display_row, 1);

    // Read the entire image
    png_bytepp image = (png_bytepp)malloc(sizeof(png_bytep) * png_get_image_height(png_ptr, info_ptr));
    for (int i = 0; i < png_get_image_height(png_ptr, info_ptr); i++) {
        image[i] = (png_bytep)malloc(png_get_rowbytes(png_ptr, info_ptr));
    }
    png_read_image(png_ptr, image);

    // Combine rows progressively
    png_progressive_combine_row(png_ptr, row, display_row);

    // Free allocated memory
    free(row);
    free(display_row);
    for (int i = 0; i < png_get_image_height(png_ptr, info_ptr); i++) {
        free(image[i]);
    }
    free(image);

    // Clean up
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    fclose(file);

    return 0;
}