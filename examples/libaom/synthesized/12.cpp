// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_img_alloc at aom_image.c:199:14 in aom_image.h
// aom_img_free at aom_image.c:303:6 in aom_image.h
// aom_img_add_metadata at aom_image.c:379:5 in aom_image.h
// aom_img_remove_metadata at aom_image.c:402:6 in aom_image.h
// aom_img_plane_height at aom_image.c:319:5 in aom_image.h
// aom_img_set_rect at aom_image.c:233:5 in aom_image.h
// aom_img_plane_width at aom_image.c:312:5 in aom_image.h
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
#include <stddef.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
  if (Size < 5) return 0;

  aom_image_t img;
  aom_img_fmt_t fmt = AOM_IMG_FMT_I420;
  unsigned int width = 128;
  unsigned int height = 128;
  if (aom_img_alloc(&img, fmt, width, height, 1) == NULL) return 0;

  // Fuzz aom_img_add_metadata
  uint32_t type = Data[0];
  size_t sz = Data[1] % 256;
  if (Size < 2 + sz) {
    aom_img_free(&img);
    return 0;
  }
  aom_metadata_insert_flags_t insert_flag = static_cast<aom_metadata_insert_flags_t>(Data[2] % 3);
  aom_img_add_metadata(&img, type, Data + 2, sz, insert_flag);

  // Fuzz aom_img_remove_metadata
  aom_img_remove_metadata(&img);

  // Fuzz aom_img_plane_height
  int plane = Data[0] % 3;
  aom_img_plane_height(&img, plane);

  // Fuzz aom_img_set_rect
  unsigned int x = Data[0] % width;
  unsigned int y = Data[1] % height;
  unsigned int w = Data[2] % (width - x + 1);
  unsigned int h = Data[3] % (height - y + 1);
  unsigned int border = Data[4] % 16;
  aom_img_set_rect(&img, x, y, w, h, border);

  // Fuzz aom_img_plane_width
  plane = Data[0] % 3;
  aom_img_plane_width(&img, plane);

  aom_img_free(&img);
  return 0;
}