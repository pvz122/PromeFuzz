// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_version_extra_str at aom_codec.c:30:13 in aom_codec.h
// aom_codec_build_config at aom_config.c:13:13 in aom_codec.h
// aom_obu_type_to_string at aom_codec.c:186:13 in aom_codec.h
// aom_codec_version_str at aom_codec.c:28:13 in aom_codec.h
// aom_codec_version at aom_codec.c:26:5 in aom_codec.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <aom.h>
#include <aom_codec.h>
#include <aom_decoder.h>
#include <aom_encoder.h>
#include <aom_image.h>
#include <aom_integer.h>
#include <aomcx.h>
#include <aomdx.h>
#include <aom_external_partition.h>
#include <aom_frame_buffer.h>
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    // Call aom_codec_version_extra_str
    const char *extra_version_str = aom_codec_version_extra_str();

    // Call aom_codec_build_config
    const char *build_config_str = aom_codec_build_config();

    // Call aom_obu_type_to_string with a valid OBU_TYPE
    OBU_TYPE obu_type = static_cast<OBU_TYPE>(Data[0] % 10); // Ensure it's within valid range
    const char *obu_type_str = aom_obu_type_to_string(obu_type);

    // Call aom_codec_version_str
    const char *version_str = aom_codec_version_str();

    // Call aom_codec_version
    int version = aom_codec_version();

    return 0;
}