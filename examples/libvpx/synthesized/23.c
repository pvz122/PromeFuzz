// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_version at vpx_codec.c:24:5 in vpx_codec.h
// vpx_codec_build_config at vpx_config.c:10:13 in vpx_codec.h
// vpx_codec_iface_name at vpx_codec.c:30:13 in vpx_codec.h
// vpx_codec_version_str at vpx_codec.c:26:13 in vpx_codec.h
// vpx_codec_version_extra_str at vpx_codec.c:28:13 in vpx_codec.h
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

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    // Test vpx_codec_version
    int version = vpx_codec_version();
    (void)version;

    // Test vpx_codec_build_config
    const char *build_config = vpx_codec_build_config();
    (void)build_config;

    // Test vpx_codec_iface_name
    const char *iface_name = vpx_codec_iface_name(NULL);
    (void)iface_name;

    // Test vpx_codec_version_str
    const char *version_str = vpx_codec_version_str();
    (void)version_str;

    // Test vpx_codec_version_extra_str
    const char *version_extra_str = vpx_codec_version_extra_str();
    (void)version_extra_str;

    // Test vpx_codec_enc_init_multi_ver
    if (Size >= sizeof(vpx_codec_enc_cfg_t) + sizeof(vpx_rational_t)) {
        vpx_codec_ctx_t ctx;
        vpx_codec_enc_cfg_t cfg;
        vpx_rational_t dsf;
        int num_enc = 1;
        vpx_codec_flags_t flags = 0;
        int ver = VPX_ENCODER_ABI_VERSION;

        memset(&ctx, 0, sizeof(vpx_codec_ctx_t));
        memcpy(&cfg, Data, sizeof(vpx_codec_enc_cfg_t));
        memcpy(&dsf, Data + sizeof(vpx_codec_enc_cfg_t), sizeof(vpx_rational_t));

        vpx_codec_err_t err = vpx_codec_enc_init_multi_ver(&ctx, vpx_codec_vp8_cx(), &cfg, num_enc, flags, &dsf, ver);
        (void)err;

        if (vpx_codec_destroy(&ctx) == VPX_CODEC_OK) {
            // Cleanup successful
        }
    }

    return 0;
}