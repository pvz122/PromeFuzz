// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_vp9_cx at vp9_cx_iface.c:2266:1 in vp8cx.h
// vpx_codec_iface_name at vpx_codec.c:30:13 in vpx_codec.h
// vpx_codec_enc_config_default at vpx_encoder.c:156:17 in vpx_encoder.h
// vpx_codec_enc_init_ver at vpx_encoder.c:30:17 in vpx_encoder.h
// vpx_codec_encode at vpx_encoder.c:192:17 in vpx_encoder.h
// vpx_codec_get_cx_data at vpx_encoder.c:247:27 in vpx_encoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vpx_encoder.h>
#include <vpx_codec.h>
#include <vp8dx.h>
#include <vp8cx.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void initialize_image(vpx_image_t *img, int width, int height) {
    memset(img, 0, sizeof(*img));
    img->fmt = VPX_IMG_FMT_I420;
    img->w = width;
    img->h = height;
    img->d_w = width;
    img->d_h = height;
    img->x_chroma_shift = 1;
    img->y_chroma_shift = 1;
    img->bps = 12;
    img->stride[VPX_PLANE_Y] = width;
    img->stride[VPX_PLANE_U] = width / 2;
    img->stride[VPX_PLANE_V] = width / 2;
    img->planes[VPX_PLANE_Y] = malloc(width * height);
    img->planes[VPX_PLANE_U] = malloc((width / 2) * (height / 2));
    img->planes[VPX_PLANE_V] = malloc((width / 2) * (height / 2));
}

static void free_image(vpx_image_t *img) {
    free(img->planes[VPX_PLANE_Y]);
    free(img->planes[VPX_PLANE_U]);
    free(img->planes[VPX_PLANE_V]);
}

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    vpx_codec_iface_t *iface = vpx_codec_vp9_cx();
    if (!iface) return 0;

    const char *name = vpx_codec_iface_name(iface);
    if (!name) return 0;

    vpx_codec_ctx_t codec;
    vpx_codec_enc_cfg_t cfg;

    if (vpx_codec_enc_config_default(iface, &cfg, 0) != VPX_CODEC_OK) return 0;

    cfg.g_w = 320;
    cfg.g_h = 240;
    cfg.g_timebase.num = 1;
    cfg.g_timebase.den = 30;
    cfg.rc_target_bitrate = 1000;

    if (vpx_codec_enc_init(&codec, iface, &cfg, 0) != VPX_CODEC_OK) return 0;

    vpx_image_t img;
    initialize_image(&img, cfg.g_w, cfg.g_h);

    vpx_codec_encode(&codec, &img, 0, 1, 0, VPX_DL_REALTIME);

    vpx_codec_iter_t iter = NULL;
    const vpx_codec_cx_pkt_t *pkt;
    while ((pkt = vpx_codec_get_cx_data(&codec, &iter)) != NULL) {
        // Process the encoded data packet
    }

    free_image(&img);
    vpx_codec_destroy(&codec);

    return 0;
}