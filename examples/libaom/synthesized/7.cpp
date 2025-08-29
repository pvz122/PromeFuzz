// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_uleb_size_in_bytes at aom_integer.c:23:8 in aom_integer.h
// aom_uleb_encode_fixed_size at aom_integer.c:79:5 in aom_integer.h
// aom_codec_av1_cx at av1_cx_iface.c:5030:20 in aomcx.h
// aom_codec_enc_config_default at aom_encoder.c:100:17 in aom_encoder.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_get_global_headers at aom_encoder.c:281:18 in aom_encoder.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
// aom_uleb_decode at aom_integer.c:31:5 in aom_integer.h
// aom_uleb_encode at aom_integer.c:58:5 in aom_integer.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "aom.h"
#include "aom_codec.h"
#include "aomcx.h"
#include "aomdx.h"
#include "aom_encoder.h"
#include "aom_decoder.h"
#include "aom_integer.h"
#include "aom_image.h"
#include "aom_external_partition.h"
#include "aom_frame_buffer.h"

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) return 0;

    // Fuzz aom_uleb_size_in_bytes
    uint64_t value;
    memcpy(&value, Data, sizeof(uint64_t));
    size_t size = aom_uleb_size_in_bytes(value);

    // Fuzz aom_uleb_encode_fixed_size
    uint8_t coded_value[16];
    size_t coded_size;
    int ret = aom_uleb_encode_fixed_size(value, sizeof(coded_value), size, coded_value, &coded_size);

    // Fuzz aom_codec_get_global_headers
    aom_codec_ctx_t ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;
    aom_codec_enc_config_default(iface, &cfg, 0);
    aom_codec_enc_init(&ctx, iface, &cfg, 0);
    aom_fixed_buf_t *headers = aom_codec_get_global_headers(&ctx);
    if (headers) {
        free(headers->buf);
        free(headers);
    }
    aom_codec_destroy(&ctx);

    // Fuzz aom_uleb_decode
    uint64_t decoded_value;
    size_t decoded_length;
    ret = aom_uleb_decode(Data, Size, &decoded_value, &decoded_length);

    // Fuzz aom_uleb_encode
    ret = aom_uleb_encode(value, sizeof(coded_value), coded_value, &coded_size);

    return 0;
}