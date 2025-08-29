// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_vp8_cx at vp8_cx_iface.c:1400:1 in vp8cx.h
// vpx_codec_iface_name at vpx_codec.c:30:13 in vpx_codec.h
// vpx_img_alloc at vpx_image.c:162:14 in vpx_image.h
// vpx_codec_enc_config_default at vpx_encoder.c:156:17 in vpx_encoder.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_codec_enc_init_ver at vpx_encoder.c:30:17 in vpx_encoder.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_codec_encode at vpx_encoder.c:192:17 in vpx_encoder.h
// vpx_codec_err_to_string at vpx_codec.c:34:13 in vpx_codec.h
// vpx_codec_get_cx_data at vpx_encoder.c:247:27 in vpx_encoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vpx/vpx_codec.h>
#include <vpx/vp8cx.h>
#include <vpx/vpx_encoder.h>
#include <vpx/vpx_image.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    vpx_codec_iface_t *iface = vpx_codec_vp8_cx();
    const char *name = vpx_codec_iface_name(iface);

    vpx_image_t *img = vpx_img_alloc(NULL, VPX_IMG_FMT_I420, 640, 480, 1);
    if (!img) return 0;

    vpx_codec_ctx_t ctx;
    vpx_codec_enc_cfg_t cfg;
    if (vpx_codec_enc_config_default(iface, &cfg, 0) != VPX_CODEC_OK) {
        vpx_img_free(img);
        return 0;
    }

    if (vpx_codec_enc_init_ver(&ctx, iface, &cfg, 0, VPX_ENCODER_ABI_VERSION) != VPX_CODEC_OK) {
        vpx_img_free(img);
        return 0;
    }

    vpx_codec_err_t err = vpx_codec_encode(&ctx, img, 0, 1, 0, VPX_DL_REALTIME);
    const char *err_str = vpx_codec_err_to_string(err);

    vpx_codec_iter_t iter = NULL;
    const vpx_codec_cx_pkt_t *pkt;
    while ((pkt = vpx_codec_get_cx_data(&ctx, &iter)) != NULL) {
        // Process the packet
    }

    vpx_codec_destroy(&ctx);
    vpx_img_free(img);

    return 0;
}