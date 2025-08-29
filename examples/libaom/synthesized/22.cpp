// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_img_alloc_with_border at aom_image.c:224:14 in aom_image.h
// aom_img_flip at aom_image.c:284:6 in aom_image.h
// aom_img_set_rect at aom_image.c:233:5 in aom_image.h
// aom_img_alloc at aom_image.c:199:14 in aom_image.h
// aom_img_wrap at aom_image.c:215:14 in aom_image.h
// aom_img_free at aom_image.c:303:6 in aom_image.h
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
#include <aom/aom_integer.h>
#include <aom/aomdx.h>
#include <aom/aom_external_partition.h>
#include <aom/aom_codec.h>
#include <aom/aomcx.h>
#include <aom/aom_decoder.h>
#include <aom/aom_frame_buffer.h>
#include <aom/aom.h>
#include <aom/aom_encoder.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < 11) return 0;

    aom_image_t img;
    aom_img_fmt_t fmt = static_cast<aom_img_fmt_t>(Data[0] % 19);
    unsigned int d_w = (Data[1] << 8) | Data[2];
    unsigned int d_h = (Data[3] << 8) | Data[4];
    unsigned int align = (Data[5] << 8) | Data[6];
    unsigned int size_align = (Data[7] << 8) | Data[8];
    unsigned int border = (Data[9] << 8) | Data[10];

    aom_img_alloc_with_border(&img, fmt, d_w, d_h, align, size_align, border);

    aom_img_flip(&img);

    if (Size >= 19) {
        unsigned int x = (Data[11] << 8) | Data[12];
        unsigned int y = (Data[13] << 8) | Data[14];
        unsigned int w = (Data[15] << 8) | Data[16];
        unsigned int h = (Data[17] << 8) | Data[18];
        aom_img_set_rect(&img, x, y, w, h, border);
    }

    aom_image_t *img_ptr = aom_img_alloc(NULL, fmt, d_w, d_h, align);

    unsigned char *img_data = (unsigned char *)malloc(d_w * d_h * 3);
    if (img_data) {
        aom_img_wrap(&img, fmt, d_w, d_h, align, img_data);
        free(img_data);
    }

    if (img_ptr) aom_img_free(img_ptr);
    aom_img_free(&img);

    return 0;
}