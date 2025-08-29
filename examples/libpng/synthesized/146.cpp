// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_write_rows at pngwrite.c:625:1 in png.h
// png_get_rows at pngget.c:50:1 in png.h
// png_save_uint_32 at pngwutil.c:41:1 in png.h
// png_chunk_warning at pngerror.c:497:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_146(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Initialize png_struct and png_info
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, nullptr);
        return 0;
    }

    // Set up error handling
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }

    // Prepare dummy file
    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }

    png_init_io(png_ptr, fp);

    // Test png_write_rows
    png_bytepp rows = (png_bytepp)malloc(sizeof(png_bytep) * 1);
    if (rows) {
        rows[0] = (png_bytep)Data;
        png_write_rows(png_ptr, rows, 1);
        free(rows);
    }

    // Test png_get_rows
    png_bytepp retrieved_rows = png_get_rows(png_ptr, info_ptr);
    if (retrieved_rows) {
        // Do nothing, just check if it returns non-null
    }

    // Test png_save_uint_32
    png_byte buf[4];
    png_save_uint_32(buf, 123456789);

    // Test png_chunk_warning
    png_chunk_warning(png_ptr, "Test warning");

    // Test png_get_uint_32
    png_uint_32 value = png_get_uint_32(Data);

    // Cleanup
    fclose(fp);
    png_destroy_write_struct(&png_ptr, &info_ptr);

    return 0;
}