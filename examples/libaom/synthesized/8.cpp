// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_dx at av1_dx_iface.c:1786:20 in aomdx.h
// aom_codec_av1_cx at av1_cx_iface.c:5030:20 in aomcx.h
// aom_codec_iface_name at aom_codec.c:32:13 in aom_codec.h
// aom_codec_iface_name at aom_codec.c:32:13 in aom_codec.h
// aom_codec_get_caps at aom_codec.c:84:18 in aom_codec.h
// aom_codec_get_caps at aom_codec.c:84:18 in aom_codec.h
// aom_codec_peek_stream_info at aom_decoder.c:57:17 in aom_decoder.h
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
#include <aom/aom_decoder.h>
#include <aom/aom_encoder.h>
#include <aom/aom_image.h>
#include <aom/aom_integer.h>
#include <aom/aomdx.h>
#include <aom/aomcx.h>
#include <aom/aom_frame_buffer.h>
#include <aom/aom_external_partition.h>

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    aom_codec_iface_t *decoder_iface = aom_codec_av1_dx();
    aom_codec_iface_t *encoder_iface = aom_codec_av1_cx();

    const char *decoder_name = aom_codec_iface_name(decoder_iface);
    const char *encoder_name = aom_codec_iface_name(encoder_iface);

    aom_codec_caps_t decoder_caps = aom_codec_get_caps(decoder_iface);
    aom_codec_caps_t encoder_caps = aom_codec_get_caps(encoder_iface);

    aom_codec_stream_info_t stream_info = {};
    stream_info.is_annexb = 0;

    aom_codec_err_t peek_result = aom_codec_peek_stream_info(decoder_iface, Data, Size, &stream_info);

    return 0;
}