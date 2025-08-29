// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_read_info at pngread.c:91:1 in png.h
// png_set_iCCP at pngset.c:864:1 in png.h
// png_get_rowbytes at pngget.c:40:1 in png.h
// png_get_rowbytes at pngget.c:40:1 in png.h
// png_read_rows at pngread.c:552:1 in png.h
// png_get_image_height at pngget.c:71:1 in png.h
// png_get_image_height at pngget.c:71:1 in png.h
// png_get_rowbytes at pngget.c:40:1 in png.h
// png_read_image at pngread.c:607:1 in png.h
// png_get_image_height at pngget.c:71:1 in png.h
// png_get_uint_31 at pngrutil.c:41:1 in png.h
// png_set_eXIf_1 at pngset.c:331:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0;

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

    // Use a dummy file for reading
    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }
    fwrite(Data, 1, Size, fp);
    fclose(fp);

    fp = fopen("./dummy_file", "rb");
    if (!fp) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }

    png_init_io(png_ptr, fp);

    // Read PNG info
    png_read_info(png_ptr, info_ptr);

    // Fuzz png_set_iCCP
    const char *name = "test_profile";
    int compression_type = 0;
    png_set_iCCP(png_ptr, info_ptr, name, compression_type, Data, Size);

    // Fuzz png_read_rows
    png_bytep row = (png_bytep)malloc(png_get_rowbytes(png_ptr, info_ptr));
    png_bytep display_row = (png_bytep)malloc(png_get_rowbytes(png_ptr, info_ptr));
    png_read_rows(png_ptr, &row, &display_row, 1);
    free(row);
    free(display_row);

    // Fuzz png_read_image
    png_bytepp image = (png_bytepp)malloc(sizeof(png_bytep) * png_get_image_height(png_ptr, info_ptr));
    for (png_uint_32 y = 0; y < png_get_image_height(png_ptr, info_ptr); y++) {
        image[y] = (png_bytep)malloc(png_get_rowbytes(png_ptr, info_ptr));
    }
    png_read_image(png_ptr, image);
    for (png_uint_32 y = 0; y < png_get_image_height(png_ptr, info_ptr); y++) {
        free(image[y]);
    }
    free(image);

    // Fuzz png_get_uint_31
    png_get_uint_31(png_ptr, Data);

    // Fuzz png_set_eXIf_1
    png_set_eXIf_1(png_ptr, info_ptr, Size, (png_bytep)Data);

    // Clean up
    fclose(fp);
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}