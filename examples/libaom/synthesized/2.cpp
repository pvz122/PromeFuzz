// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_img_add_metadata at aom_image.c:379:5 in aom_image.h
// aom_img_remove_metadata at aom_image.c:402:6 in aom_image.h
// aom_img_plane_height at aom_image.c:319:5 in aom_image.h
// aom_img_plane_width at aom_image.c:312:5 in aom_image.h
// aom_img_set_rect at aom_image.c:233:5 in aom_image.h
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
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    aom_image_t img;
    img.fmt = AOM_IMG_FMT_I420;
    img.w = 128;
    img.h = 128;
    img.d_w = 128;
    img.d_h = 128;
    img.range = AOM_CR_STUDIO_RANGE;
    img.csp = AOM_CSP_VERTICAL;
    img.mc = AOM_CICP_MC_BT_709;
    img.tc = AOM_CICP_TC_BT_709;
    img.cp = AOM_CICP_CP_BT_709;
    img.monochrome = 0;
    img.metadata = nullptr;

    size_t sz = Data[1] % 256;
    if (sz > Size - 2) sz = Size - 2;

    aom_img_add_metadata(&img, 1, Data + 2, sz, AOM_MIF_ANY_FRAME);
    aom_img_remove_metadata(&img);

    aom_img_plane_height(&img, 0);
    aom_img_plane_width(&img, 0);

    aom_img_set_rect(&img, 0, 0, 64, 64, 0);

    return 0;
}