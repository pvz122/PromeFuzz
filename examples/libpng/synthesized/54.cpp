// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_get_compression_buffer_size at pngget.c:1290:1 in png.h
// png_read_rows at pngread.c:552:1 in png.h
// png_set_write_status_fn at pngwrite.c:1367:1 in png.h
// png_get_chunk_cache_max at pngget.c:1329:1 in png.h
// png_set_chunk_cache_max at pngset.c:1819:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
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

    // Use the first byte to determine which function to fuzz
    uint8_t function_selector = Data[0] % 5;
    Data++;
    Size--;

    switch (function_selector) {
        case 0: {
            // Fuzz png_get_compression_buffer_size
            size_t buffer_size = png_get_compression_buffer_size(png_ptr);
            break;
        }
        case 1: {
            // Fuzz png_read_rows
            if (Size < sizeof(png_uint_32)) break;
            png_uint_32 num_rows = *reinterpret_cast<const png_uint_32*>(Data);
            Data += sizeof(png_uint_32);
            Size -= sizeof(png_uint_32);

            png_bytepp row = nullptr;
            png_bytepp display_row = nullptr;
            png_read_rows(png_ptr, row, display_row, num_rows);
            break;
        }
        case 2: {
            // Fuzz png_set_write_status_fn
            png_set_write_status_fn(png_ptr, nullptr);
            break;
        }
        case 3: {
            // Fuzz png_get_chunk_cache_max
            png_uint_32 chunk_cache_max = png_get_chunk_cache_max(png_ptr);
            break;
        }
        case 4: {
            // Fuzz png_set_chunk_cache_max
            if (Size < sizeof(png_uint_32)) break;
            png_uint_32 user_chunk_cache_max = *reinterpret_cast<const png_uint_32*>(Data);
            png_set_chunk_cache_max(png_ptr, user_chunk_cache_max);
            break;
        }
        default:
            break;
    }

    // Clean up
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}