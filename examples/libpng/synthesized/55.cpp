// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_read_info at pngread.c:91:1 in png.h
// png_get_IHDR at pngget.c:939:1 in png.h
// png_get_sCAL_s at pngget.c:1078:1 in png.h
// png_get_iCCP at pngget.c:718:1 in png.h
// png_get_pCAL at pngget.c:1005:1 in png.h
// png_read_update_info at pngread.c:170:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0; // PNG files start with an 8-byte header

    // Write the input data to a dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy file for reading
    file = fopen("./dummy_file", "rb");
    if (!file) return 0;

    // Initialize libpng structures
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) {
        fclose(file);
        return 0;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        fclose(file);
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        fclose(file);
        return 0;
    }

    png_init_io(png_ptr, file);
    png_read_info(png_ptr, info_ptr);

    // Fuzz png_get_IHDR
    png_uint_32 width, height;
    int bit_depth, color_type, interlace_method, compression_method, filter_method;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_method, &compression_method, &filter_method);

    // Fuzz png_get_sCAL_s
    int unit;
    png_charp swidth, sheight;
    png_get_sCAL_s(png_ptr, info_ptr, &unit, &swidth, &sheight);

    // Fuzz png_get_iCCP
    png_charp name;
    int compression_type;
    png_bytep profile;
    png_uint_32 proflen;
    png_get_iCCP(png_ptr, info_ptr, &name, &compression_type, &profile, &proflen);

    // Fuzz png_get_pCAL
    png_charp purpose, units;
    png_int_32 X0, X1;
    int type, nparams;
    png_charpp params;
    png_get_pCAL(png_ptr, info_ptr, &purpose, &X0, &X1, &type, &nparams, &units, &params);

    // Fuzz png_read_update_info
    png_read_update_info(png_ptr, info_ptr);

    // Cleanup
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    fclose(file);

    return 0;
}