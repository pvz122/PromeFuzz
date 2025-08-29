// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5030:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_error at aom_codec.c:56:13 in aom_codec.h
// aom_codec_get_cx_data at aom_encoder.c:198:27 in aom_encoder.h
// aom_codec_set_option at aom_codec.c:119:17 in aom_codec.h
// aom_codec_error_detail at aom_codec.c:61:13 in aom_codec.h
// aom_codec_decode at aom_decoder.c:94:17 in aom_decoder.h
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
#include <aom/aom_encoder.h>
#include <aom/aom_image.h>
#include <aom/aom_integer.h>
#include <aom/aomcx.h>
#include <aom/aomdx.h>
#include <aom/aom_external_partition.h>
#include <aom/aom_frame_buffer.h>

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    aom_codec_ctx_t ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_err_t res = aom_codec_enc_init(&ctx, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    const char *error_msg = aom_codec_error(&ctx);
    (void)error_msg;

    aom_codec_iter_t iter = nullptr;
    const aom_codec_cx_pkt_t *pkt = aom_codec_get_cx_data(&ctx, &iter);
    (void)pkt;

    const char *option_name = "option_name";
    const char *option_value = "option_value";
    res = aom_codec_set_option(&ctx, option_name, option_value);
    (void)res;

    const char *error_detail = aom_codec_error_detail(&ctx);
    (void)error_detail;

    res = aom_codec_decode(&ctx, Data, Size, nullptr);
    (void)res;

    aom_codec_destroy(&ctx);
    return 0;
}