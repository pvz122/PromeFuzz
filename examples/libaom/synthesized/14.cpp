// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_dx at av1_dx_iface.c:1786:20 in aomdx.h
// aom_codec_dec_init_ver at aom_decoder.c:25:17 in aom_decoder.h
// aom_codec_decode at aom_decoder.c:94:17 in aom_decoder.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_get_preview_frame at aom_encoder.c:264:20 in aom_encoder.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "aom.h"
#include "aom_codec.h"
#include "aom_decoder.h"
#include "aom_encoder.h"
#include "aom_image.h"
#include "aom_integer.h"
#include "aomcx.h"
#include "aomdx.h"
#include "aom_external_partition.h"
#include "aom_frame_buffer.h"

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    aom_codec_ctx_t ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx();

    if (aom_codec_dec_init(&ctx, iface, nullptr, 0) != AOM_CODEC_OK) {
        return 0;
    }

    aom_codec_decode(&ctx, Data, Size, nullptr);

    aom_codec_control(&ctx, AOME_SET_CPUUSED, 8);

    const aom_image_t *preview_frame = aom_codec_get_preview_frame(&ctx);
    if (preview_frame) {
        // Do not modify the preview frame
    }

    aom_codec_destroy(&ctx);

    return 0;
}