// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_img_get_metadata at aom_image.c:409:23 in aom_image.h
// aom_img_add_metadata at aom_image.c:379:5 in aom_image.h
// aom_img_remove_metadata at aom_image.c:402:6 in aom_image.h
// aom_img_num_metadata at aom_image.c:419:8 in aom_image.h
// aom_img_metadata_alloc at aom_image.c:326:17 in aom_image.h
// aom_img_add_metadata at aom_image.c:379:5 in aom_image.h
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
#include <aom/aom_decoder.h>
#include <aom/aom_encoder.h>
#include <aom/aom_external_partition.h>
#include <aom/aom_frame_buffer.h>
#include <aom/aom_integer.h>
#include <aom/aomcx.h>
#include <aom/aomdx.h>
#include <stddef.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    aom_image_t img;
    img.fmt = AOM_IMG_FMT_I420;
    img.cp = AOM_CICP_CP_BT_709;
    img.tc = AOM_CICP_TC_BT_709;
    img.mc = AOM_CICP_MC_BT_709;
    img.monochrome = 0;
    img.csp = AOM_CSP_VERTICAL;
    img.range = AOM_CR_STUDIO_RANGE;
    img.w = 128;
    img.planes[0] = nullptr;
    img.planes[1] = nullptr;
    img.planes[2] = nullptr;
    img.stride[0] = 0;
    img.stride[1] = 0;
    img.stride[2] = 0;
    img.sz = 0;
    img.user_priv = nullptr;
    img.img_data = nullptr;
    img.metadata = nullptr;

    size_t index = Data[0] % 256;
    const aom_metadata_t *metadata = aom_img_get_metadata(&img, index);

    uint32_t type = Data[1] % 256;
    size_t sz = Data[1] % 256;
    if (sz > Size - 2) sz = Size - 2;
    aom_metadata_insert_flags_t insert_flag = static_cast<aom_metadata_insert_flags_t>(Data[1] % 3);
    int add_result = aom_img_add_metadata(&img, type, Data + 2, sz, insert_flag);

    aom_img_remove_metadata(&img);

    size_t num_metadata = aom_img_num_metadata(&img);

    aom_metadata_t *alloc_metadata = aom_img_metadata_alloc(type, Data + 2, sz, insert_flag);
    if (alloc_metadata) {
        aom_img_add_metadata(&img, alloc_metadata->type, alloc_metadata->payload, alloc_metadata->sz, alloc_metadata->insert_flag);
    }

    return 0;
}