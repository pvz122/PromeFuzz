// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_uleb_size_in_bytes at aom_integer.c:23:8 in aom_integer.h
// aom_uleb_encode_fixed_size at aom_integer.c:79:5 in aom_integer.h
// aom_uleb_decode at aom_integer.c:31:5 in aom_integer.h
// aom_codec_av1_cx at av1_cx_iface.c:5030:20 in aomcx.h
// aom_codec_enc_config_default at aom_encoder.c:100:17 in aom_encoder.h
// aom_codec_enc_config_set at aom_encoder.c:298:17 in aom_encoder.h
// aom_uleb_encode at aom_integer.c:58:5 in aom_integer.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "aom.h"
#include "aom_codec.h"
#include "aom_encoder.h"
#include "aomcx.h"
#include "aomdx.h"
#include "aom_image.h"
#include "aom_integer.h"

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
  if (Size < sizeof(uint64_t)) return 0;

  uint64_t value = *reinterpret_cast<const uint64_t*>(Data);
  size_t available = Size - sizeof(uint64_t);
  const uint8_t* buffer = Data + sizeof(uint64_t);

  // Test aom_uleb_size_in_bytes
  size_t size_in_bytes = aom_uleb_size_in_bytes(value);

  // Test aom_uleb_encode_fixed_size
  uint8_t coded_value[16];
  size_t coded_size;
  aom_uleb_encode_fixed_size(value, sizeof(coded_value), size_in_bytes, coded_value, &coded_size);

  // Test aom_uleb_decode
  uint64_t decoded_value;
  size_t decoded_length;
  aom_uleb_decode(buffer, available, &decoded_value, &decoded_length);

  // Test aom_codec_enc_config_set
  aom_codec_ctx_t ctx;
  aom_codec_enc_cfg_t cfg;
  if (aom_codec_enc_config_default(aom_codec_av1_cx(), &cfg, 0) == AOM_CODEC_OK) {
    aom_codec_enc_config_set(&ctx, &cfg);
  }

  // Test aom_uleb_encode
  aom_uleb_encode(value, sizeof(coded_value), coded_value, &coded_size);

  return 0;
}