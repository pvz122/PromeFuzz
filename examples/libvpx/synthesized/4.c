// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_img_alloc at vpx_image.c:162:14 in vpx_image.h
// vpx_codec_vp8_cx at vp8_cx_iface.c:1400:1 in vp8cx.h
// vpx_codec_iface_name at vpx_codec.c:30:13 in vpx_codec.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_codec_enc_config_default at vpx_encoder.c:156:17 in vpx_encoder.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_codec_enc_init_ver at vpx_encoder.c:30:17 in vpx_encoder.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_codec_control_ at vpx_codec.c:89:17 in vpx_codec.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vpx/vpx_codec.h>
#include <vpx/vp8dx.h>
#include <vpx/vp8cx.h>
#include <vpx/vpx_encoder.h>
#include <vpx/vpx_image.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    vpx_image_t *img = vpx_img_alloc(NULL, VPX_IMG_FMT_I420, 128, 128, 1);
    if (!img) return 0;

    const vpx_codec_iface_t *iface = vpx_codec_vp8_cx();
    const char *iface_name = vpx_codec_iface_name(iface);
    if (!iface_name) {
        vpx_img_free(img);
        return 0;
    }

    vpx_codec_enc_cfg_t cfg;
    if (vpx_codec_enc_config_default(iface, &cfg, 0) != VPX_CODEC_OK) {
        vpx_img_free(img);
        return 0;
    }

    vpx_codec_ctx_t ctx;
    if (vpx_codec_enc_init_ver(&ctx, iface, &cfg, 0, VPX_ENCODER_ABI_VERSION) != VPX_CODEC_OK) {
        vpx_img_free(img);
        return 0;
    }

    if (vpx_codec_control_(&ctx, VP8E_SET_CPUUSED, 4) != VPX_CODEC_OK) {
        vpx_codec_destroy(&ctx);
        vpx_img_free(img);
        return 0;
    }

    vpx_img_free(img);
    vpx_codec_destroy(&ctx);

    return 0;
}