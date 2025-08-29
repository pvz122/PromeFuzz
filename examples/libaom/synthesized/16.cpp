// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_dx at av1_dx_iface.c:1786:20 in aomdx.h
// aom_codec_dec_init_ver at aom_decoder.c:25:17 in aom_decoder.h
// aom_codec_set_frame_buffer_functions at aom_decoder.c:120:17 in aom_decoder.h
// aom_codec_get_frame at aom_decoder.c:109:14 in aom_decoder.h
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
#include <aom/aomdx.h>
#include <aom/aom_integer.h>
#include <aom/aom_image.h>
#include <aom/aom_codec.h>
#include <aom/aom_external_partition.h>
#include <aom/aomcx.h>
#include <aom/aom_decoder.h>
#include <aom/aom_frame_buffer.h>
#include <aom/aom.h>
#include <aom/aom_encoder.h>

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx();
    aom_codec_dec_cfg_t cfg = {0};
    cfg.threads = 1;

    if (aom_codec_dec_init_ver(&ctx, iface, &cfg, 0, AOM_DECODER_ABI_VERSION) != AOM_CODEC_OK) {
        return 0;
    }

    aom_get_frame_buffer_cb_fn_t cb_get = nullptr;
    aom_release_frame_buffer_cb_fn_t cb_release = nullptr;
    void *cb_priv = nullptr;

    aom_codec_set_frame_buffer_functions(&ctx, cb_get, cb_release, cb_priv);

    aom_codec_iter_t iter = nullptr;
    aom_codec_get_frame(&ctx, &iter);

    int ctrl_id = Data[0] % 256;
    aom_codec_control(&ctx, ctrl_id, nullptr);

    aom_codec_get_preview_frame(&ctx);

    aom_codec_destroy(&ctx);

    return 0;
}