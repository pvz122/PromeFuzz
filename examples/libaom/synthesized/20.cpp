// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_dx at av1_dx_iface.c:1786:20 in aomdx.h
// aom_codec_dec_init_ver at aom_decoder.c:25:17 in aom_decoder.h
// aom_codec_set_frame_buffer_functions at aom_decoder.c:120:17 in aom_decoder.h
// aom_codec_decode at aom_decoder.c:94:17 in aom_decoder.h
// aom_codec_get_frame at aom_decoder.c:109:14 in aom_decoder.h
// aom_codec_set_option at aom_codec.c:119:17 in aom_codec.h
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
#include <aom.h>
#include <aom_codec.h>
#include <aom_decoder.h>
#include <aomdx.h>
#include <aom_image.h>
#include <aom_frame_buffer.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

static aom_codec_ctx_t codec_ctx;
static aom_image_t img;
static aom_codec_iter_t iter = nullptr;

static int get_frame_buffer(void *cb_priv, size_t min_size, aom_codec_frame_buffer_t *fb) {
    fb->data = static_cast<uint8_t *>(malloc(min_size));
    fb->size = min_size;
    return 0;
}

static int release_frame_buffer(void *cb_priv, aom_codec_frame_buffer_t *fb) {
    free(fb->data);
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    aom_codec_iface_t *iface = aom_codec_av1_dx();
    if (aom_codec_dec_init(&codec_ctx, iface, nullptr, 0) != AOM_CODEC_OK) {
        return 0;
    }

    aom_codec_set_frame_buffer_functions(&codec_ctx, get_frame_buffer, release_frame_buffer, nullptr);

    aom_codec_decode(&codec_ctx, data, size, nullptr);

    while (aom_codec_get_frame(&codec_ctx, &iter) != nullptr) {}

    aom_codec_set_option(&codec_ctx, "option_name", "option_value");

    aom_codec_destroy(&codec_ctx);

    return 0;
}