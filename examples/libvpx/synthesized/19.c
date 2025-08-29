// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_vp8_cx at vp8_cx_iface.c:1400:1 in vp8cx.h
// vpx_codec_enc_config_default at vpx_encoder.c:156:17 in vpx_encoder.h
// vpx_codec_enc_init_ver at vpx_encoder.c:30:17 in vpx_encoder.h
// vpx_codec_error_detail at vpx_codec.c:59:13 in vpx_codec.h
// vpx_codec_control_ at vpx_codec.c:89:17 in vpx_codec.h
// vpx_codec_error at vpx_codec.c:54:13 in vpx_codec.h
// vpx_codec_get_global_headers at vpx_encoder.c:330:18 in vpx_encoder.h
// vpx_codec_encode at vpx_encoder.c:192:17 in vpx_encoder.h
// vpx_codec_err_to_string at vpx_codec.c:34:13 in vpx_codec.h
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

int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    vpx_codec_ctx_t ctx;
    vpx_codec_iface_t *iface = vpx_codec_vp8_cx();
    vpx_codec_enc_cfg_t cfg;

    if (vpx_codec_enc_config_default(iface, &cfg, 0)) return 0;

    if (vpx_codec_enc_init(&ctx, iface, &cfg, 0)) return 0;

    // Fuzz vpx_codec_error_detail
    const char *error_detail = vpx_codec_error_detail(&ctx);

    // Fuzz vpx_codec_control_
    int ctrl_id = Data[0] % 100;
    vpx_codec_control_(&ctx, ctrl_id, NULL);

    // Fuzz vpx_codec_error
    const char *error = vpx_codec_error(&ctx);

    // Fuzz vpx_codec_get_global_headers
    vpx_fixed_buf_t *headers = vpx_codec_get_global_headers(&ctx);

    // Fuzz vpx_codec_encode
    vpx_image_t img;
    memset(&img, 0, sizeof(img));
    img.fmt = VPX_IMG_FMT_I420;
    img.w = 64;
    img.h = 64;
    img.bit_depth = 8;
    img.d_w = 64;
    img.d_h = 64;
    img.r_w = 64;
    img.r_h = 64;
    img.x_chroma_shift = 1;
    img.y_chroma_shift = 1;
    img.planes[0] = (unsigned char *)Data;
    img.planes[1] = (unsigned char *)Data;
    img.planes[2] = (unsigned char *)Data;
    img.stride[0] = 64;
    img.stride[1] = 32;
    img.stride[2] = 32;

    vpx_codec_encode(&ctx, &img, 0, 1, 0, VPX_DL_REALTIME);

    // Fuzz vpx_codec_err_to_string
    vpx_codec_err_t err = (vpx_codec_err_t)(Data[0] % 10);
    const char *err_str = vpx_codec_err_to_string(err);

    vpx_codec_destroy(&ctx);

    return 0;
}