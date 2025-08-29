// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_img_alloc at vpx_image.c:162:14 in vpx_image.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_img_wrap at vpx_image.c:168:14 in vpx_image.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_img_flip at vpx_image.c:229:6 in vpx_image.h
// vpx_img_set_rect at vpx_image.c:176:5 in vpx_image.h
// vpx_codec_get_preview_frame at vpx_encoder.c:313:20 in vpx_encoder.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vpx_encoder.h>
#include <vpx_image.h>
#include <vp8dx.h>
#include <vp8cx.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < 5) return 0;

    // Initialize image descriptor
    vpx_image_t img;
    memset(&img, 0, sizeof(img));

    // Randomly select an image format
    vpx_img_fmt_t fmt = (vpx_img_fmt_t)(Data[0] % 16);
    unsigned int width = 64;
    unsigned int height = 64;
    unsigned int align = 16;

    // Allocate image
    vpx_image_t *img_ptr = vpx_img_alloc(NULL, fmt, width, height, align);
    if (!img_ptr) return 0;

    // Wrap image
    unsigned char *img_data = (unsigned char *)malloc(width * height * 3);
    if (!img_data) {
        vpx_img_free(img_ptr);
        return 0;
    }
    vpx_image_t *wrapped_img = vpx_img_wrap(&img, fmt, width, height, align, img_data);
    if (!wrapped_img) {
        free(img_data);
        vpx_img_free(img_ptr);
        return 0;
    }

    // Flip image
    vpx_img_flip(img_ptr);

    // Set image rectangle
    unsigned int x = Data[1] % width;
    unsigned int y = Data[2] % height;
    unsigned int w = Data[3] % (width - x);
    unsigned int h = Data[4] % (height - y);
    vpx_img_set_rect(img_ptr, x, y, w, h);

    // Get preview frame (requires a codec context)
    vpx_codec_ctx_t ctx;
    memset(&ctx, 0, sizeof(ctx));
    const vpx_image_t *preview_frame = vpx_codec_get_preview_frame(&ctx);

    // Free resources
    vpx_img_free(img_ptr);
    free(img_data);

    return 0;
}