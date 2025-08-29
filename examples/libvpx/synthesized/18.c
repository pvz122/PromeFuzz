// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_vp8_cx at vp8_cx_iface.c:1400:1 in vp8cx.h
// vpx_codec_enc_config_default at vpx_encoder.c:156:17 in vpx_encoder.h
// vpx_codec_enc_init_ver at vpx_encoder.c:30:17 in vpx_encoder.h
// vpx_img_alloc at vpx_image.c:162:14 in vpx_image.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_codec_control_ at vpx_codec.c:89:17 in vpx_codec.h
// vpx_codec_set_cx_data_buf at vpx_encoder.c:293:17 in vpx_encoder.h
// vpx_codec_vp8_dx at vp8_dx_iface.c:726:1 in vp8dx.h
// vpx_codec_dec_init_ver at vpx_decoder.c:24:17 in vpx_decoder.h
// vpx_codec_decode at vpx_decoder.c:104:17 in vpx_decoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_codec_encode at vpx_encoder.c:192:17 in vpx_encoder.h
// vpx_codec_set_frame_buffer_functions at vpx_decoder.c:173:17 in vpx_decoder.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vpx/vpx_codec.h>
#include <vpx/vp8dx.h>
#include <vpx/vpx_decoder.h>
#include <vpx/vp8cx.h>
#include <vpx/vpx_encoder.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static vpx_codec_ctx_t codec_ctx;
static vpx_codec_enc_cfg_t cfg;
static vpx_image_t img;
static vpx_fixed_buf_t buf;

static void initialize_codec() {
    vpx_codec_iface_t *iface = vpx_codec_vp8_cx();
    vpx_codec_enc_config_default(iface, &cfg, 0);
    cfg.g_w = 320;
    cfg.g_h = 240;
    cfg.g_timebase.num = 1;
    cfg.g_timebase.den = 30;
    cfg.rc_target_bitrate = 1000;
    vpx_codec_enc_init(&codec_ctx, iface, &cfg, 0);
    vpx_img_alloc(&img, VPX_IMG_FMT_I420, 320, 240, 1);
}

static void cleanup_codec() {
    vpx_img_free(&img);
    vpx_codec_destroy(&codec_ctx);
}

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    initialize_codec();

    int ctrl_id = data[0] % 256;
    vpx_codec_control_(&codec_ctx, ctrl_id, NULL);

    buf.buf = malloc(size);
    buf.sz = size;
    if (buf.buf) {
        memcpy(buf.buf, data, size);
        vpx_codec_set_cx_data_buf(&codec_ctx, &buf, 0, 0);
    }

    if (size > 0) {
        vpx_codec_ctx_t dec_ctx;
        vpx_codec_iface_t *dec_iface = vpx_codec_vp8_dx();
        if (vpx_codec_dec_init(&dec_ctx, dec_iface, NULL, 0) == VPX_CODEC_OK) {
            vpx_codec_decode(&dec_ctx, data, size, NULL, 0);
            vpx_codec_destroy(&dec_ctx);
        }
    }

    vpx_codec_encode(&codec_ctx, &img, 0, 1, 0, 0);

    vpx_codec_set_frame_buffer_functions(&codec_ctx, NULL, NULL, NULL);

    if (buf.buf) {
        free(buf.buf);
    }
    cleanup_codec();

    return 0;
}