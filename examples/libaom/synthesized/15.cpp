// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_uleb_size_in_bytes at aom_integer.c:23:8 in aom_integer.h
// aom_uleb_encode at aom_integer.c:58:5 in aom_integer.h
// aom_uleb_decode at aom_integer.c:31:5 in aom_integer.h
// aom_uleb_encode_fixed_size at aom_integer.c:79:5 in aom_integer.h
// aom_uleb_decode at aom_integer.c:31:5 in aom_integer.h
// aom_codec_av1_cx at av1_cx_iface.c:5030:20 in aomcx.h
// aom_codec_enc_config_default at aom_encoder.c:100:17 in aom_encoder.h
// aom_codec_enc_config_set at aom_encoder.c:298:17 in aom_encoder.h
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
#include <aom/aom_encoder.h>
#include <aom/aom_decoder.h>
#include <aom/aom_integer.h>
#include <aom/aomdx.h>
#include <aom/aom_image.h>
#include <aom/aom_external_partition.h>
#include <aom/aom_frame_buffer.h>
#include <aom/aomcx.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) return 0;

    uint64_t value = *reinterpret_cast<const uint64_t*>(Data);
    size_t uleb_size = aom_uleb_size_in_bytes(value);

    uint8_t buffer[16];
    size_t coded_size;
    int encode_result = aom_uleb_encode(value, sizeof(buffer), buffer, &coded_size);
    if (encode_result == 0) {
        uint64_t decoded_value;
        size_t decoded_length;
        int decode_result = aom_uleb_decode(buffer, coded_size, &decoded_value, &decoded_length);
        if (decode_result == 0 && decoded_value != value) {
            return 0;
        }
    }

    int encode_fixed_result = aom_uleb_encode_fixed_size(value, sizeof(buffer), uleb_size, buffer, &coded_size);
    if (encode_fixed_result == 0) {
        uint64_t decoded_value;
        size_t decoded_length;
        int decode_result = aom_uleb_decode(buffer, coded_size, &decoded_value, &decoded_length);
        if (decode_result == 0 && decoded_value != value) {
            return 0;
        }
    }

    aom_codec_ctx_t ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;
    aom_codec_enc_config_default(iface, &cfg, 0);
    aom_codec_err_t enc_config_result = aom_codec_enc_config_set(&ctx, &cfg);
    if (enc_config_result != AOM_CODEC_OK) {
        return 0;
    }

    return 0;
}