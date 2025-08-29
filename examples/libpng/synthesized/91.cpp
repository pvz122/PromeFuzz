// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_get_libpng_ver at png.c:837:1 in png.h
// png_access_version_number at png.c:986:1 in png.h
// png_read_rows at pngread.c:552:1 in png.h
// png_get_user_chunk_ptr at pngget.c:1283:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize libpng structures
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

    // Fuzz png_get_libpng_ver
    png_const_charp version = png_get_libpng_ver(png_ptr);
    (void)version;

    // Fuzz png_access_version_number
    png_uint_32 version_number = png_access_version_number();
    (void)version_number;

    // Fuzz png_read_rows
    png_bytep row = (png_bytep)malloc(Size);
    if (row) {
        png_bytepp row_ptr = &row;
        png_read_rows(png_ptr, row_ptr, nullptr, 1);
        free(row);
    }

    // Fuzz png_get_user_chunk_ptr
    png_voidp user_chunk_ptr = png_get_user_chunk_ptr(png_ptr);
    (void)user_chunk_ptr;

    // Fuzz png_set_eXIf_1
    png_bytep exif_data = (png_bytep)malloc(Size);
    if (exif_data) {
        memcpy(exif_data, Data, Size);
        png_set_eXIf_1(png_ptr, info_ptr, Size, exif_data);
        free(exif_data);
    }

    // Cleanup
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}