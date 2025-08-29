// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_vp8_dx at vp8_dx_iface.c:726:1 in vp8dx.h
// vpx_codec_iface_name at vpx_codec.c:30:13 in vpx_codec.h
// vpx_codec_dec_init_ver at vpx_decoder.c:24:17 in vpx_decoder.h
// vpx_codec_decode at vpx_decoder.c:104:17 in vpx_decoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_codec_get_frame at vpx_decoder.c:122:14 in vpx_decoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vpx/vpx_codec.h>
#include <vpx/vp8dx.h>
#include <vpx/vpx_decoder.h>
#include <vpx/vp8cx.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    vpx_codec_ctx_t ctx;
    vpx_codec_iface_t *iface = vpx_codec_vp8_dx();
    vpx_codec_dec_cfg_t cfg = {0, 0, 0};
    vpx_codec_iter_t iter = NULL;
    vpx_image_t *img;

    const char *name = vpx_codec_iface_name(iface);
    if (name == NULL) {
        return 0;
    }

    if (vpx_codec_dec_init_ver(&ctx, iface, &cfg, 0, VPX_DECODER_ABI_VERSION) != VPX_CODEC_OK) {
        return 0;
    }

    if (vpx_codec_decode(&ctx, Data, Size, NULL, 0) != VPX_CODEC_OK) {
        vpx_codec_destroy(&ctx);
        return 0;
    }

    while ((img = vpx_codec_get_frame(&ctx, &iter)) != NULL) {
        // Do nothing, just iterate over frames
    }

    vpx_codec_destroy(&ctx);
    return 0;
}