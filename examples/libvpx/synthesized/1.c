// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_vp9_dx at vp9_dx_iface.c:712:1 in vp8dx.h
// vpx_codec_vp8_dx at vp8_dx_iface.c:726:1 in vp8dx.h
// vpx_codec_dec_init_ver at vpx_decoder.c:24:17 in vpx_decoder.h
// vpx_codec_decode at vpx_decoder.c:104:17 in vpx_decoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_codec_dec_init_ver at vpx_decoder.c:24:17 in vpx_decoder.h
// vpx_codec_decode at vpx_decoder.c:104:17 in vpx_decoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vpx_codec.h>
#include <vp8dx.h>
#include <vpx_decoder.h>
#include <vp8cx.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    vpx_codec_ctx_t ctx;
    vpx_codec_iface_t *iface_vp9 = vpx_codec_vp9_dx();
    vpx_codec_iface_t *iface_vp8 = vpx_codec_vp8_dx();
    vpx_codec_dec_cfg_t cfg = {0, 0, 0};

    // Initialize VP9 decoder
    if (vpx_codec_dec_init_ver(&ctx, iface_vp9, &cfg, 0, VPX_DECODER_ABI_VERSION) == VPX_CODEC_OK) {
        vpx_codec_decode(&ctx, Data, Size, NULL, 0);
        vpx_codec_destroy(&ctx);
    }

    // Initialize VP8 decoder
    if (vpx_codec_dec_init_ver(&ctx, iface_vp8, &cfg, 0, VPX_DECODER_ABI_VERSION) == VPX_CODEC_OK) {
        vpx_codec_decode(&ctx, Data, Size, NULL, 0);
        vpx_codec_destroy(&ctx);
    }

    return 0;
}