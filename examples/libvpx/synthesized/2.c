// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_vp8_cx at vp8_cx_iface.c:1400:1 in vp8cx.h
// vpx_codec_enc_config_default at vpx_encoder.c:156:17 in vpx_encoder.h
// vpx_codec_enc_init_ver at vpx_encoder.c:30:17 in vpx_encoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_img_wrap at vpx_image.c:168:14 in vpx_image.h
// vpx_codec_encode at vpx_encoder.c:192:17 in vpx_encoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
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

int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    vpx_codec_iface_t *iface = vpx_codec_vp8_cx();
    vpx_codec_enc_cfg_t cfg;
    vpx_codec_ctx_t codec;
    vpx_image_t img;

    if (vpx_codec_enc_config_default(iface, &cfg, 0) != VPX_CODEC_OK) {
        return 0;
    }

    if (vpx_codec_enc_init(&codec, iface, &cfg, 0) != VPX_CODEC_OK) {
        return 0;
    }

    // Ensure the input data is large enough for the image dimensions
    size_t required_size = cfg.g_w * cfg.g_h * 3 / 2; // I420 format requires 1.5 bytes per pixel
    if (Size < required_size) {
        vpx_codec_destroy(&codec);
        return 0;
    }

    unsigned char *img_data = (unsigned char *)Data;
    vpx_img_wrap(&img, VPX_IMG_FMT_I420, cfg.g_w, cfg.g_h, 1, img_data);

    if (vpx_codec_encode(&codec, &img, 0, 1, 0, VPX_DL_REALTIME) != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec);
        return 0;
    }

    vpx_codec_destroy(&codec);
    return 0;
}