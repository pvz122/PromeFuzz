// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_img_alloc at aom_image.c:199:14 in aom_image.h
// aom_img_add_metadata at aom_image.c:379:5 in aom_image.h
// aom_img_num_metadata at aom_image.c:419:8 in aom_image.h
// aom_img_remove_metadata at aom_image.c:402:6 in aom_image.h
// aom_img_metadata_alloc at aom_image.c:326:17 in aom_image.h
// aom_img_metadata_free at aom_image.c:344:6 in aom_image.h
// aom_img_free at aom_image.c:303:6 in aom_image.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <aom/aom_image.h>
#include <aom/aom_codec.h>
#include <aom/aom_encoder.h>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h>
#include <aom/aomcx.h>
#include <aom/aom_integer.h>
#include <aom/aom_external_partition.h>
#include <aom/aom_frame_buffer.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 3) return 0;

    aom_image_t img;
    aom_img_fmt_t fmt = AOM_IMG_FMT_I420;
    unsigned int width = 128;
    unsigned int height = 128;
    aom_img_alloc(&img, fmt, width, height, 1);

    uint32_t type = Data[0];
    size_t sz = Data[1] % 256;
    if (sz > Size - 3) sz = Size - 3;

    aom_metadata_insert_flags_t insert_flag = static_cast<aom_metadata_insert_flags_t>(Data[2] % 3);

    aom_img_add_metadata(&img, type, Data + 3, sz, insert_flag);

    size_t num_metadata = aom_img_num_metadata(&img);

    aom_img_remove_metadata(&img);

    aom_metadata_t *metadata = aom_img_metadata_alloc(type, Data + 3, sz, insert_flag);
    if (metadata) {
        aom_img_metadata_free(metadata);
    }

    aom_img_free(&img);

    return 0;
}