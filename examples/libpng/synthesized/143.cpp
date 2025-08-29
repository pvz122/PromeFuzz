// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_get_compression_buffer_size at pngget.c:1290:1 in png.h
// png_get_compression_type at pngget.c:116:1 in png.h
// png_chunk_warning at pngerror.c:497:1 in png.h
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_write_chunk at pngwutil.c:209:1 in png.h
// png_destroy_info_struct at png.c:394:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_143(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Initialize png_struct and png_info
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    // Fuzz png_get_compression_buffer_size
    size_t buffer_size = png_get_compression_buffer_size(png_ptr);

    // Fuzz png_get_compression_type
    png_byte compression_type = png_get_compression_type(png_ptr, info_ptr);

    // Fuzz png_chunk_warning
    png_chunk_warning(png_ptr, "Fuzzing warning message");

    // Fuzz png_get_int_32
    png_int_32 int_value = png_get_int_32(Data);

    // Fuzz png_write_chunk
    if (Size >= 8) {
        png_structp write_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        if (write_ptr) {
            png_infop write_info_ptr = png_create_info_struct(write_ptr);
            if (write_info_ptr) {
                FILE *dummy_file = fopen("./dummy_file", "wb");
                if (dummy_file) {
                    png_init_io(write_ptr, dummy_file);
                    png_write_chunk(write_ptr, Data, Data + 4, Size - 4);
                    fclose(dummy_file);
                }
                png_destroy_info_struct(write_ptr, &write_info_ptr);
            }
            png_destroy_write_struct(&write_ptr, nullptr);
        }
    }

    // Cleanup
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}