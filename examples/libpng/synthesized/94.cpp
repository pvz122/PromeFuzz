// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_set_IHDR at pngset.c:429:1 in png.h
// png_set_rows at pngset.c:1709:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_write_png at pngwrite.c:1395:1 in png.h
// png_handle_as_unknown at png.c:926:1 in png.h
// png_set_gamma_fixed at pngrtran.c:870:1 in png.h
// png_set_unknown_chunks at pngset.c:1360:1 in png.h
// png_set_keep_unknown_chunks at pngset.c:1532:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize PNG structures
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, nullptr);
        return 0;
    }

    // Set up dummy file
    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }
    png_init_io(png_ptr, fp);

    // Set up image dimensions and row pointers
    png_set_IHDR(png_ptr, info_ptr, 1, 1, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_bytep row_pointers[1];
    row_pointers[0] = (png_bytep)malloc(3);
    if (row_pointers[0]) {
        memset(row_pointers[0], 0, 3);
        png_set_rows(png_ptr, info_ptr, row_pointers);
    }

    // Fuzz png_write_png
    if (setjmp(png_jmpbuf(png_ptr))) {
        if (row_pointers[0]) free(row_pointers[0]);
        fclose(fp);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, nullptr);

    // Fuzz png_handle_as_unknown
    png_byte chunk_name[5] = {0};
    if (Size >= 5) {
        memcpy(chunk_name, Data, 5);
    }
    png_handle_as_unknown(png_ptr, chunk_name);

    // Fuzz png_set_gamma_fixed
    png_set_gamma_fixed(png_ptr, 45455, 45455);

    // Fuzz png_set_unknown_chunks
    png_unknown_chunk unknown_chunk;
    if (Size >= 5) {
        memcpy(unknown_chunk.name, Data, 5);
    }
    unknown_chunk.data = nullptr;
    unknown_chunk.size = 0;
    unknown_chunk.location = 0;
    png_set_unknown_chunks(png_ptr, info_ptr, &unknown_chunk, 1);

    // Fuzz png_set_keep_unknown_chunks
    png_set_keep_unknown_chunks(png_ptr, PNG_HANDLE_CHUNK_AS_DEFAULT, chunk_name, 1);

    if (row_pointers[0]) free(row_pointers[0]);
    fclose(fp);
    png_destroy_write_struct(&png_ptr, &info_ptr);

    return 0;
}