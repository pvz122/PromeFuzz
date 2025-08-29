// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_set_benign_errors at pngset.c:1858:1 in png.h
// png_set_text_compression_mem_level at pngwrite.c:1303:1 in png.h
// png_set_text_compression_window_bits at pngwrite.c:1328:1 in png.h
// png_set_text_compression_strategy at pngwrite.c:1314:1 in png.h
// png_image_write_to_memory at pngwrite.c:2266:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize png_struct and png_image
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_image image;
    memset(&image, 0, sizeof(image));
    image.version = PNG_IMAGE_VERSION;

    // Fuzz png_set_benign_errors
    png_set_benign_errors(png_ptr, Data[0] % 2);

    // Fuzz png_set_text_compression_mem_level
    png_set_text_compression_mem_level(png_ptr, Data[0] % 10);

    // Fuzz png_set_text_compression_window_bits
    png_set_text_compression_window_bits(png_ptr, 8 + (Data[0] % 8));

    // Fuzz png_set_text_compression_strategy
    png_set_text_compression_strategy(png_ptr, Data[0] % 4);

    // Fuzz png_image_write_to_memory
    png_alloc_size_t memory_bytes = 0;
    png_image_write_to_memory(&image, nullptr, &memory_bytes, Data[0] % 2, nullptr, 0, nullptr);

    // Cleanup
    png_destroy_write_struct(&png_ptr, nullptr);

    return 0;
}