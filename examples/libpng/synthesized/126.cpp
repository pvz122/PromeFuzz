// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_write_sig at pngwutil.c:68:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_write_image at pngwrite.c:647:1 in png.h
// png_write_flush at pngwrite.c:966:1 in png.h
// png_write_row at pngwrite.c:744:1 in png.h
// png_write_chunk_end at pngwutil.c:163:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_126(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    FILE *fp = fopen("./dummy_file", "wb");
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

    png_write_sig(png_ptr);

    png_bytepp image = (png_bytepp)malloc(sizeof(png_bytep) * 1);
    if (!image) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        return 0;
    }

    image[0] = (png_bytep)malloc(Size);
    if (!image[0]) {
        free(image);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        return 0;
    }

    memcpy(image[0], Data, Size);

    png_write_image(png_ptr, image);

    png_write_flush(png_ptr);

    png_write_row(png_ptr, image[0]);

    png_write_chunk_end(png_ptr);

    free(image[0]);
    free(image);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);

    return 0;
}