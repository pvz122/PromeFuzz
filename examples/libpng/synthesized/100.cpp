// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_create_read_struct_2 at pngread.c:39:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_error_fn at pngerror.c:835:1 in png.h
// png_get_error_ptr at pngerror.c:856:1 in png.h
// png_error at pngerror.c:38:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_create_write_struct_2 at pngwrite.c:556:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_set_error_fn at pngerror.c:835:1 in png.h
// png_get_error_ptr at pngerror.c:856:1 in png.h
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

static void custom_error_fn(png_structp png_ptr, png_const_charp error_msg) {
    (void)png_ptr;
    (void)error_msg;
    longjmp(png_jmpbuf(png_ptr), 1);
}

static void custom_warning_fn(png_structp png_ptr, png_const_charp warning_msg) {
    (void)png_ptr;
    (void)warning_msg;
}

static void* custom_malloc_fn(png_structp png_ptr, png_alloc_size_t size) {
    (void)png_ptr;
    return malloc(size);
}

static void custom_free_fn(png_structp png_ptr, png_voidp ptr) {
    (void)png_ptr;
    free(ptr);
}

extern "C" int LLVMFuzzerTestOneInput_100(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_read_ptr = png_create_read_struct_2(
        PNG_LIBPNG_VER_STRING, nullptr, custom_error_fn, custom_warning_fn,
        nullptr, custom_malloc_fn, custom_free_fn);

    if (png_read_ptr) {
        if (setjmp(png_jmpbuf(png_read_ptr))) {
            png_destroy_read_struct(&png_read_ptr, nullptr, nullptr);
            return 0;
        }
        png_set_error_fn(png_read_ptr, nullptr, custom_error_fn, custom_warning_fn);
        png_get_error_ptr(png_read_ptr);
        png_error(png_read_ptr, "Fuzz error");
        png_destroy_read_struct(&png_read_ptr, nullptr, nullptr);
    }

    png_structp png_write_ptr = png_create_write_struct_2(
        PNG_LIBPNG_VER_STRING, nullptr, custom_error_fn, custom_warning_fn,
        nullptr, custom_malloc_fn, custom_free_fn);

    if (png_write_ptr) {
        if (setjmp(png_jmpbuf(png_write_ptr))) {
            png_destroy_write_struct(&png_write_ptr, nullptr);
            return 0;
        }
        png_set_error_fn(png_write_ptr, nullptr, custom_error_fn, custom_warning_fn);
        png_get_error_ptr(png_write_ptr);
        png_destroy_write_struct(&png_write_ptr, nullptr);
    }

    return 0;
}