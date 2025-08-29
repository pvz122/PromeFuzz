// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct_2 at pngread.c:39:1 in png.h
// png_create_write_struct_2 at pngwrite.c:556:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_error_fn at pngerror.c:835:1 in png.h
// png_set_error_fn at pngerror.c:835:1 in png.h
// png_get_error_ptr at pngerror.c:856:1 in png.h
// png_error at pngerror.c:38:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
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

static void dummy_error_fn(png_structp png_ptr, png_const_charp error_msg) {}
static void dummy_warning_fn(png_structp png_ptr, png_const_charp warning_msg) {}
static void* dummy_malloc_fn(png_structp png_ptr, png_alloc_size_t size) { return malloc(size); }
static void dummy_free_fn(png_structp png_ptr, void* ptr) { free(ptr); }

extern "C" int LLVMFuzzerTestOneInput_111(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp read_struct = png_create_read_struct_2(
        PNG_LIBPNG_VER_STRING, nullptr, dummy_error_fn, dummy_warning_fn,
        nullptr, dummy_malloc_fn, dummy_free_fn
    );
    if (!read_struct) return 0;

    png_structp write_struct = png_create_write_struct_2(
        PNG_LIBPNG_VER_STRING, nullptr, dummy_error_fn, dummy_warning_fn,
        nullptr, dummy_malloc_fn, dummy_free_fn
    );
    if (!write_struct) {
        png_destroy_read_struct(&read_struct, nullptr, nullptr);
        return 0;
    }

    png_set_error_fn(read_struct, nullptr, dummy_error_fn, dummy_warning_fn);
    png_set_error_fn(write_struct, nullptr, dummy_error_fn, dummy_warning_fn);

    png_voidp error_ptr = png_get_error_ptr(read_struct);
    if (error_ptr != nullptr) {
        png_error(read_struct, "Dummy error");
    }

    png_destroy_read_struct(&read_struct, nullptr, nullptr);
    png_destroy_write_struct(&write_struct, nullptr);

    return 0;
}