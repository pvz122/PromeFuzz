// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_tRNS at pngset.c:1149:1 in png.h
// png_set_rows at pngset.c:1709:1 in png.h
// png_get_color_type at pngget.c:89:1 in png.h
// png_set_cICP at pngset.c:136:1 in png.h
// png_read_image at pngread.c:607:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
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

    // Use the first byte to determine which function to fuzz
    uint8_t function_selector = Data[0] % 5;
    Data++;
    Size--;

    switch (function_selector) {
        case 0: {
            png_byte trans_alpha[256];
            int num_trans = Size > 256 ? 256 : Size;
            memcpy(trans_alpha, Data, num_trans);
            png_color_16 trans_color = {0, 0, 0, 0, 0};
            png_set_tRNS(png_ptr, info_ptr, trans_alpha, num_trans, &trans_color);
            break;
        }
        case 1: {
            png_bytep row_pointers[1];
            row_pointers[0] = (png_bytep)Data;
            png_set_rows(png_ptr, info_ptr, row_pointers);
            break;
        }
        case 2: {
            png_byte color_type = png_get_color_type(png_ptr, info_ptr);
            break;
        }
        case 3: {
            if (Size < 4) break;
            png_byte colour_primaries = Data[0];
            png_byte transfer_function = Data[1];
            png_byte matrix_coefficients = Data[2];
            png_byte video_full_range_flag = Data[3];
            png_set_cICP(png_ptr, info_ptr, colour_primaries, transfer_function, matrix_coefficients, video_full_range_flag);
            break;
        }
        case 4: {
            png_bytep image[1];
            image[0] = (png_bytep)Data;
            png_read_image(png_ptr, image);
            break;
        }
        default:
            break;
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}