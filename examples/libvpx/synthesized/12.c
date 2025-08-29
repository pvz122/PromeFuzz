// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_version at vpx_codec.c:24:5 in vpx_codec.h
// vpx_codec_iface_name at vpx_codec.c:30:13 in vpx_codec.h
// vpx_codec_vp8_cx at vp8_cx_iface.c:1400:1 in vp8cx.h
// vpx_codec_version_str at vpx_codec.c:26:13 in vpx_codec.h
// vpx_codec_version_extra_str at vpx_codec.c:28:13 in vpx_codec.h
// vpx_codec_enc_config_default at vpx_encoder.c:156:17 in vpx_encoder.h
// vpx_codec_vp8_cx at vp8_cx_iface.c:1400:1 in vp8cx.h
// vpx_codec_enc_init_multi_ver at vpx_encoder.c:70:17 in vpx_encoder.h
// vpx_codec_vp8_cx at vp8_cx_iface.c:1400:1 in vp8cx.h
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

int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    // Test vpx_codec_version
    int version = vpx_codec_version();
    (void)version;

    // Test vpx_codec_iface_name
    const char *iface_name = vpx_codec_iface_name(vpx_codec_vp8_cx());
    (void)iface_name;

    // Test vpx_codec_version_str
    const char *version_str = vpx_codec_version_str();
    (void)version_str;

    // Test vpx_codec_version_extra_str
    const char *version_extra_str = vpx_codec_version_extra_str();
    (void)version_extra_str;

    // Test vpx_codec_enc_config_default
    vpx_codec_enc_cfg_t cfg;
    vpx_codec_err_t err = vpx_codec_enc_config_default(vpx_codec_vp8_cx(), &cfg, 0);
    (void)err;

    // Test vpx_codec_enc_init_multi_ver
    vpx_codec_ctx_t ctx;
    vpx_rational_t dsf = {1, 1};
    err = vpx_codec_enc_init_multi_ver(&ctx, vpx_codec_vp8_cx(), &cfg, 1, 0, &dsf, VPX_ENCODER_ABI_VERSION);
    if (err == VPX_CODEC_OK) {
        vpx_codec_destroy(&ctx);
    }

    return 0;
}