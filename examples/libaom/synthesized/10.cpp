// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_dx at av1_dx_iface.c:1786:20 in aomdx.h
// aom_codec_dec_init_ver at aom_decoder.c:25:17 in aom_decoder.h
// aom_codec_peek_stream_info at aom_decoder.c:57:17 in aom_decoder.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
// aom_codec_decode at aom_decoder.c:94:17 in aom_decoder.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
// aom_codec_get_stream_info at aom_decoder.c:75:17 in aom_decoder.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
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
#include <aom/aom.h>
#include <aom/aom_codec.h>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h>
#include <aom/aom_image.h>
#include <aom/aom_integer.h>
#include <aom/aom_external_partition.h>
#include <aom/aomcx.h>
#include <aom/aom_encoder.h>
#include <aom/aom_frame_buffer.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    aom_codec_ctx_t ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx();
    aom_codec_dec_cfg_t cfg = {0, 0, 0};
    aom_codec_err_t res = aom_codec_dec_init(&ctx, iface, &cfg, 0);
    if (res != AOM_CODEC_OK) return 0;

    aom_codec_stream_info_t si;
    si.is_annexb = 1;
    res = aom_codec_peek_stream_info(iface, data, size, &si);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&ctx);
        return 0;
    }

    res = aom_codec_decode(&ctx, data, size, nullptr);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&ctx);
        return 0;
    }

    res = aom_codec_get_stream_info(&ctx, &si);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&ctx);
        return 0;
    }

    aom_fixed_buf_t *headers = aom_codec_get_global_headers(&ctx);
    if (headers) {
        free(headers->buf);
        free(headers);
    }

    aom_codec_destroy(&ctx);
    return 0;
}