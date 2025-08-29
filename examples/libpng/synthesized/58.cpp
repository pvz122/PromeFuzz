// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_write_sig at pngwutil.c:68:1 in png.h
// png_write_chunk at pngwutil.c:209:1 in png.h
// png_write_chunk_data at pngwutil.c:144:1 in png.h
// png_write_row at pngwrite.c:744:1 in png.h
// png_write_image at pngwrite.c:647:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, nullptr);
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }

    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }

    png_init_io(png_ptr, fp);

    // Test png_write_sig
    png_write_sig(png_ptr);

    // Test png_write_chunk
    if (Size >= 8) {
        png_write_chunk(png_ptr, reinterpret_cast<png_const_bytep>(Data), reinterpret_cast<png_const_bytep>(Data + 4), Size - 4);
    }

    // Test png_write_chunk_data
    if (Size > 0) {
        png_write_chunk_data(png_ptr, reinterpret_cast<png_const_bytep>(Data), Size);
    }

    // Test png_write_row
    if (Size > 0) {
        png_bytep row = reinterpret_cast<png_bytep>(const_cast<uint8_t*>(Data));
        png_write_row(png_ptr, row);
    }

    // Test png_write_image
    if (Size > 0) {
        png_bytepp image = new png_bytep[1];
        image[0] = reinterpret_cast<png_bytep>(const_cast<uint8_t*>(Data));
        png_write_image(png_ptr, image);
        delete[] image;
    }

    fclose(fp);
    png_destroy_write_struct(&png_ptr, &info_ptr);

    return 0;
}