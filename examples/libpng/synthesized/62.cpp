// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_tRNS_to_alpha at pngrtran.c:980:1 in png.h
// png_set_user_transform_info at pngtrans.c:805:1 in png.h
// png_set_filter_heuristics at pngwrite.c:1175:1 in png.h
// png_set_pCAL at pngset.c:487:1 in png.h
// png_set_text_compression_mem_level at pngwrite.c:1303:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    // Fuzz png_set_tRNS_to_alpha
    png_set_tRNS_to_alpha(png_ptr);

    // Fuzz png_set_user_transform_info
    int user_transform_depth = Data[0] % 16;
    int user_transform_channels = Data[0] % 5;
    png_set_user_transform_info(png_ptr, nullptr, user_transform_depth, user_transform_channels);

    // Fuzz png_set_filter_heuristics
    double filter_weights[] = {1.0, 2.0, 3.0};
    double filter_costs[] = {1.0, 2.0, 3.0};
    png_set_filter_heuristics(png_ptr, Data[0] % 3, 3, filter_weights, filter_costs);

    // Fuzz png_set_pCAL
    const char* purpose = "fuzz";
    png_int_32 X0 = 0;
    png_int_32 X1 = 100;
    int type = Data[0] % 3;
    int nparams = Data[0] % 5;
    const char* units = "units";
    const char* params[] = {"param1", "param2", "param3", "param4", "param5"};
    png_set_pCAL(png_ptr, info_ptr, purpose, X0, X1, type, nparams, units, const_cast<png_charpp>(params));

    // Fuzz png_set_text_compression_mem_level
    int mem_level = Data[0] % 9;
    png_set_text_compression_mem_level(png_ptr, mem_level);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}