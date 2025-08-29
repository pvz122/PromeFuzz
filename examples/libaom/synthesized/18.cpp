// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_version_extra_str at aom_codec.c:30:13 in aom_codec.h
// aom_codec_build_config at aom_config.c:13:13 in aom_codec.h
// aom_codec_version_str at aom_codec.c:28:13 in aom_codec.h
// aom_codec_iface_name at aom_codec.c:32:13 in aom_codec.h
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
#include <aom/aom.h>
#include <aom/aom_codec.h>
#include <aom/aom_decoder.h>
#include <aom/aom_encoder.h>
#include <aom/aom_image.h>
#include <aom/aom_integer.h>
#include <aom/aomcx.h>
#include <aom/aomdx.h>
#include <aom/aom_external_partition.h>
#include <aom/aom_frame_buffer.h>

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    // Call aom_codec_version_extra_str
    const char *extra_version = aom_codec_version_extra_str();

    // Call aom_codec_build_config
    const char *build_config = aom_codec_build_config();

    // Call aom_codec_version_str
    const char *version_str = aom_codec_version_str();

    // Call aom_codec_iface_name with a null pointer
    const char *iface_name_null = aom_codec_iface_name(nullptr);

    // Call aom_codec_version
    int version = aom_codec_version();

    return 0;
}