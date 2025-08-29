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
// png_get_hIST at pngget.c:922:1 in png.h
// png_set_hIST at pngset.c:387:1 in png.h
// png_malloc at pngmem.c:169:1 in png.h
// png_malloc at pngmem.c:169:1 in png.h
// png_set_rows at pngset.c:1709:1 in png.h
// png_write_info at pngwrite.c:223:1 in png.h
// png_free at pngmem.c:230:1 in png.h
// png_free at pngmem.c:230:1 in png.h
// png_destroy_info_struct at png.c:394:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_128(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

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

    // Simulate reading from a file
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
    png_read_info(png_ptr, info_ptr);

    // Fuzz png_get_hIST
    png_uint_16p hist;
    png_get_hIST(png_ptr, info_ptr, &hist);

    // Fuzz png_set_hIST
    png_uint_16 hist_data[256];
    for (int i = 0; i < 256; ++i) {
        hist_data[i] = i;
    }
    png_set_hIST(png_ptr, info_ptr, hist_data);

    // Fuzz png_set_rows
    png_bytepp row_pointers = (png_bytepp)png_malloc(png_ptr, sizeof(png_bytep) * 1);
    row_pointers[0] = (png_bytep)png_malloc(png_ptr, 1);
    png_set_rows(png_ptr, info_ptr, row_pointers);

    // Fuzz png_write_info
    png_write_info(png_ptr, info_ptr);

    // Cleanup
    png_free(png_ptr, row_pointers[0]);
    png_free(png_ptr, row_pointers);
    png_destroy_info_struct(png_ptr, &info_ptr);
    png_destroy_read_struct(&png_ptr, nullptr, nullptr);
    fclose(fp);

    return 0;
}