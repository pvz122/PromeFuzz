// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_dx at av1_dx_iface.c:1786:20 in aomdx.h
// aom_codec_dec_init_ver at aom_decoder.c:25:17 in aom_decoder.h
// aom_codec_peek_stream_info at aom_decoder.c:57:17 in aom_decoder.h
// aom_codec_decode at aom_decoder.c:94:17 in aom_decoder.h
// aom_codec_get_stream_info at aom_decoder.c:75:17 in aom_decoder.h
// aom_codec_get_global_headers at aom_encoder.c:281:18 in aom_encoder.h
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
#include "aomdx.h"
#include "aom_image.h"
#include "aom_integer.h"
#include "aom_external_partition.h"
#include "aomcx.h"
#include "aom_encoder.h"
#include "aom_frame_buffer.h"

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    aom_codec_ctx_t ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx();
    aom_codec_stream_info_t si;
    aom_codec_dec_cfg_t cfg = {0, 0, 0};

    if (aom_codec_dec_init(&ctx, iface, &cfg, 0) != AOM_CODEC_OK) {
        return 0;
    }

    aom_codec_peek_stream_info(iface, data, size, &si);
    aom_codec_decode(&ctx, data, size, nullptr);
    aom_codec_get_stream_info(&ctx, &si);

    aom_fixed_buf_t *global_headers = aom_codec_get_global_headers(&ctx);
    if (global_headers) {
        free(global_headers->buf);
        free(global_headers);
    }

    aom_codec_destroy(&ctx);

    return 0;
}