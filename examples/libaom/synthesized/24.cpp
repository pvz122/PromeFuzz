// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_img_alloc_with_border at aom_image.c:224:14 in aom_image.h
// aom_img_flip at aom_image.c:284:6 in aom_image.h
// aom_img_free at aom_image.c:303:6 in aom_image.h
// aom_img_alloc at aom_image.c:199:14 in aom_image.h
// aom_img_flip at aom_image.c:284:6 in aom_image.h
// aom_img_free at aom_image.c:303:6 in aom_image.h
// aom_img_wrap at aom_image.c:215:14 in aom_image.h
// aom_img_flip at aom_image.c:284:6 in aom_image.h
// aom_img_free at aom_image.c:303:6 in aom_image.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <aom/aom_image.h>
#include <aom/aom_codec.h>
#include <aom/aomcx.h>
#include <aom/aomdx.h>
#include <aom/aom_encoder.h>
#include <aom/aom_decoder.h>
#include <aom/aom_external_partition.h>
#include <aom/aom_frame_buffer.h>
#include <aom/aom_integer.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 11) return 0;

    aom_image_t img;
    aom_img_fmt_t fmt = static_cast<aom_img_fmt_t>(Data[0] % (AOM_IMG_FMT_I44416 + 1));
    unsigned int d_w = (Data[1] << 8) | Data[2];
    unsigned int d_h = (Data[3] << 8) | Data[4];
    unsigned int align = (Data[5] << 8) | Data[6];
    unsigned int size_align = (Data[7] << 8) | Data[8];
    unsigned int border = (Data[9] << 8) | Data[10];

    aom_image_t *img_ptr = aom_img_alloc_with_border(NULL, fmt, d_w, d_h, align, size_align, border);
    if (img_ptr) {
        aom_img_flip(img_ptr);
        aom_img_free(img_ptr);
    }

    img_ptr = aom_img_alloc(NULL, fmt, d_w, d_h, align);
    if (img_ptr) {
        aom_img_flip(img_ptr);
        aom_img_free(img_ptr);
    }

    unsigned char *img_data = (unsigned char *)malloc(d_w * d_h * 3);
    if (img_data) {
        img_ptr = aom_img_wrap(NULL, fmt, d_w, d_h, align, img_data);
        if (img_ptr) {
            aom_img_flip(img_ptr);
            aom_img_free(img_ptr);
        }
        free(img_data);
    }

    return 0;
}