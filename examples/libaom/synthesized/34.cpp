// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5030:20 in aomcx.h
// aom_codec_enc_config_default at aom_encoder.c:100:17 in aom_encoder.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_error at aom_codec.c:56:13 in aom_codec.h
// aom_codec_get_cx_data at aom_encoder.c:198:27 in aom_encoder.h
// aom_codec_set_option at aom_codec.c:119:17 in aom_codec.h
// aom_codec_error_detail at aom_codec.c:61:13 in aom_codec.h
// aom_codec_err_to_string at aom_codec.c:36:13 in aom_codec.h
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
#include <aom/aom_codec.h>
#include <aom/aom_encoder.h>
#include <aom/aom_decoder.h>
#include <aom/aom_image.h>
#include <aom/aom_integer.h>
#include <aom/aomcx.h>
#include <aom/aomdx.h>
#include <aom/aom_external_partition.h>
#include <aom/aom_frame_buffer.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;

    if (aom_codec_enc_config_default(iface, &cfg, 0) != AOM_CODEC_OK) {
        return 0;
    }

    if (aom_codec_enc_init(&ctx, iface, &cfg, 0) != AOM_CODEC_OK) {
        return 0;
    }

    // Fuzz aom_codec_error
    const char *error_msg = aom_codec_error(&ctx);

    // Fuzz aom_codec_get_cx_data
    aom_codec_iter_t iter = nullptr;
    const aom_codec_cx_pkt_t *pkt = aom_codec_get_cx_data(&ctx, &iter);

    // Fuzz aom_codec_set_option
    char name[256];
    char value[256];
    if (Size > 512) {
        memcpy(name, Data, 256);
        memcpy(value, Data + 256, 256);
        aom_codec_set_option(&ctx, name, value);
    }

    // Fuzz aom_codec_error_detail
    const char *error_detail = aom_codec_error_detail(&ctx);

    // Fuzz aom_codec_err_to_string
    aom_codec_err_t err = static_cast<aom_codec_err_t>(Data[0] % 10);
    const char *err_str = aom_codec_err_to_string(err);

    aom_codec_destroy(&ctx);

    return 0;
}