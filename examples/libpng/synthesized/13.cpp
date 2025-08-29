// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_set_IHDR at pngset.c:429:1 in png.h
// png_write_info at pngwrite.c:223:1 in png.h
// png_write_rows at pngwrite.c:625:1 in png.h
// png_write_image at pngwrite.c:647:1 in png.h
// png_write_flush at pngwrite.c:966:1 in png.h
// png_free_default at pngmem.c:243:1 in png.h
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
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) return 0;

    fwrite(Data, 1, Size, fp);
    fclose(fp);

    fp = fopen("./dummy_file", "rb");
    if (!fp) return 0;

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) {
        fclose(fp);
        return 0;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, nullptr);
        fclose(fp);
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        return 0;
    }

    png_init_io(png_ptr, fp);

    png_set_IHDR(png_ptr, info_ptr, 32, 32, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);

    png_bytepp row_pointers = (png_bytepp)malloc(32 * sizeof(png_bytep));
    for (int y = 0; y < 32; y++) {
        row_pointers[y] = (png_bytep)malloc(3 * 32);
        memset(row_pointers[y], 0, 3 * 32);
    }

    png_write_rows(png_ptr, row_pointers, 32);
    png_write_image(png_ptr, row_pointers);
    png_write_flush(png_ptr);

    for (int y = 0; y < 32; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);

    png_free_default(png_ptr, info_ptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);

    return 0;
}