// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_vp8_dx at vp8_dx_iface.c:726:1 in vp8dx.h
// vpx_codec_dec_init_ver at vpx_decoder.c:24:17 in vpx_decoder.h
// vpx_codec_peek_stream_info at vpx_decoder.c:65:17 in vpx_decoder.h
// vpx_codec_decode at vpx_decoder.c:104:17 in vpx_decoder.h
// vpx_codec_get_caps at vpx_codec.c:85:18 in vpx_codec.h
// vpx_codec_iface_name at vpx_codec.c:30:13 in vpx_codec.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vpx_codec.h>
#include <vp8dx.h>
#include <vpx_decoder.h>
#include <vp8cx.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    vpx_codec_ctx_t ctx;
    vpx_codec_iface_t *iface = vpx_codec_vp8_dx();
    vpx_codec_dec_cfg_t cfg = {0};
    vpx_codec_stream_info_t si = {0};
    si.sz = sizeof(si);

    // Initialize decoder
    if (vpx_codec_dec_init_ver(&ctx, iface, &cfg, 0, VPX_DECODER_ABI_VERSION) != VPX_CODEC_OK) {
        return 0;
    }

    // Peek stream info
    vpx_codec_peek_stream_info(iface, data, size, &si);

    // Decode data
    vpx_codec_decode(&ctx, data, size, NULL, 0);

    // Get codec capabilities
    vpx_codec_get_caps(iface);

    // Get codec interface name
    vpx_codec_iface_name(iface);

    // Destroy codec instance
    vpx_codec_destroy(&ctx);

    return 0;
}