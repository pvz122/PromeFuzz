// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_vp8_cx at vp8_cx_iface.c:1400:1 in vp8cx.h
// vpx_codec_enc_config_default at vpx_encoder.c:156:17 in vpx_encoder.h
// vpx_codec_enc_init_ver at vpx_encoder.c:30:17 in vpx_encoder.h
// vpx_codec_encode at vpx_encoder.c:192:17 in vpx_encoder.h
// vpx_codec_get_cx_data at vpx_encoder.c:247:27 in vpx_encoder.h
// vpx_codec_error_detail at vpx_codec.c:59:13 in vpx_codec.h
// vpx_codec_control_ at vpx_codec.c:89:17 in vpx_codec.h
// vpx_codec_get_global_headers at vpx_encoder.c:330:18 in vpx_encoder.h
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

int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    vpx_codec_ctx_t ctx;
    vpx_codec_iface_t *iface = vpx_codec_vp8_cx();
    vpx_codec_enc_cfg_t cfg;

    if (vpx_codec_enc_config_default(iface, &cfg, 0)) return 0;

    if (vpx_codec_enc_init(&ctx, iface, &cfg, 0)) return 0;

    vpx_image_t img;
    img.fmt = VPX_IMG_FMT_I420;
    img.w = 128;
    img.h = 128;
    img.bit_depth = 8;
    img.d_w = 128;
    img.d_h = 128;
    img.r_w = 128;
    img.r_h = 128;
    img.x_chroma_shift = 1;
    img.y_chroma_shift = 1;
    img.planes[0] = (unsigned char *)Data;
    img.planes[1] = (unsigned char *)Data + 128 * 128;
    img.planes[2] = (unsigned char *)Data + 128 * 128 * 5 / 4;
    img.stride[0] = 128;
    img.stride[1] = 128 / 2;
    img.stride[2] = 128 / 2;

    vpx_codec_encode(&ctx, &img, 0, 1, 0, VPX_DL_REALTIME);

    vpx_codec_iter_t iter = NULL;
    const vpx_codec_cx_pkt_t *pkt;
    while ((pkt = vpx_codec_get_cx_data(&ctx, &iter)) != NULL) {
        if (pkt->kind == VPX_CODEC_CX_FRAME_PKT) {
            // Process the frame packet
        }
    }

    const char *error_detail = vpx_codec_error_detail(&ctx);
    if (error_detail) {
        // Handle error detail
    }

    vpx_codec_control_(&ctx, VP8E_SET_CPUUSED, 1);

    vpx_fixed_buf_t *global_headers = vpx_codec_get_global_headers(&ctx);
    if (global_headers) {
        // Process global headers
    }

    vpx_codec_destroy(&ctx);

    return 0;
}