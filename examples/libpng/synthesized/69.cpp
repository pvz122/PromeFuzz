// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_text at pngset.c:917:1 in png.h
// png_get_text at pngget.c:1169:1 in png.h
// png_free_data at png.c:478:1 in png.h
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_69(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    png_text text;
    char *text_buffer = new char[Size];
    std::memcpy(text_buffer, Data, Size - 1);
    text_buffer[Size - 1] = '\0';
    text.compression = -1;
    text.key = (png_charp)"fuzz_key";
    text.text = text_buffer;
    text.text_length = Size - 1;

    png_set_text(png_ptr, info_ptr, &text, 1);

    png_textp text_ptr;
    int num_text;
    png_get_text(png_ptr, info_ptr, &text_ptr, &num_text);

    png_free_data(png_ptr, info_ptr, PNG_FREE_TEXT, -1);

    png_destroy_info_struct(png_ptr, &info_ptr);

    png_destroy_read_struct(&png_ptr, nullptr, nullptr);

    delete[] text_buffer;

    return 0;
}