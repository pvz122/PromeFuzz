// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_enc_config_default at vpx_encoder.c:156:17 in vpx_encoder.h
// vpx_codec_vp9_cx at vp9_cx_iface.c:2266:1 in vp8cx.h
// vpx_codec_vp8_cx at vp8_cx_iface.c:1400:1 in vp8cx.h
// vpx_codec_enc_config_default at vpx_encoder.c:156:17 in vpx_encoder.h
// vpx_codec_enc_init_ver at vpx_encoder.c:30:17 in vpx_encoder.h
// vpx_codec_iface_name at vpx_codec.c:30:13 in vpx_codec.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_codec_get_cx_data at vpx_encoder.c:247:27 in vpx_encoder.h
// vpx_codec_enc_config_set at vpx_encoder.c:347:17 in vpx_encoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_codec_enc_config_default at vpx_encoder.c:156:17 in vpx_encoder.h
// vpx_codec_enc_init_ver at vpx_encoder.c:30:17 in vpx_encoder.h
// vpx_codec_iface_name at vpx_codec.c:30:13 in vpx_codec.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_codec_get_cx_data at vpx_encoder.c:247:27 in vpx_encoder.h
// vpx_codec_enc_config_set at vpx_encoder.c:347:17 in vpx_encoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vpx/vpx_encoder.h>
#include <vpx/vpx_codec.h>
#include <vpx/vp8dx.h>
#include <vpx/vp8cx.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void initialize_encoder_config(vpx_codec_enc_cfg_t *cfg, vpx_codec_iface_t *iface) {
    vpx_codec_enc_config_default(iface, cfg, 0);
    cfg->g_w = 640;
    cfg->g_h = 480;
    cfg->rc_target_bitrate = 1000;
}

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    vpx_codec_ctx_t codec;
    vpx_codec_enc_cfg_t cfg;
    vpx_codec_iface_t *iface_vp9 = vpx_codec_vp9_cx();
    vpx_codec_iface_t *iface_vp8 = vpx_codec_vp8_cx();

    if (vpx_codec_enc_config_default(iface_vp9, &cfg, 0) != VPX_CODEC_OK) {
        return 0;
    }

    initialize_encoder_config(&cfg, iface_vp9);

    if (vpx_codec_enc_init(&codec, iface_vp9, &cfg, 0) != VPX_CODEC_OK) {
        return 0;
    }

    const char *name = vpx_codec_iface_name(iface_vp9);
    if (name == NULL) {
        vpx_codec_destroy(&codec);
        return 0;
    }

    vpx_codec_iter_t iter = NULL;
    const vpx_codec_cx_pkt_t *pkt;
    while ((pkt = vpx_codec_get_cx_data(&codec, &iter)) != NULL) {
        // Process the packet
    }

    if (vpx_codec_enc_config_set(&codec, &cfg) != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec);
        return 0;
    }

    vpx_codec_destroy(&codec);

    if (vpx_codec_enc_config_default(iface_vp8, &cfg, 0) != VPX_CODEC_OK) {
        return 0;
    }

    initialize_encoder_config(&cfg, iface_vp8);

    if (vpx_codec_enc_init(&codec, iface_vp8, &cfg, 0) != VPX_CODEC_OK) {
        return 0;
    }

    name = vpx_codec_iface_name(iface_vp8);
    if (name == NULL) {
        vpx_codec_destroy(&codec);
        return 0;
    }

    iter = NULL;
    while ((pkt = vpx_codec_get_cx_data(&codec, &iter)) != NULL) {
        // Process the packet
    }

    if (vpx_codec_enc_config_set(&codec, &cfg) != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec);
        return 0;
    }

    vpx_codec_destroy(&codec);

    return 0;
}