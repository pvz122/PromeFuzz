// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit2_ at inflate.c:178:13 in zlib.h
// inflate at inflate.c:590:13 in zlib.h
// inflateEnd at inflate.c:1266:13 in zlib.h
// inflateEnd at inflate.c:1266:13 in zlib.h
// inflateBackInit_ at infback.c:25:13 in zlib.h
// inflateBack at infback.c:242:13 in zlib.h
// inflateBackEnd at infback.c:621:13 in zlib.h
// inflateBackEnd at infback.c:621:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static unsigned char window[32768];

static unsigned my_in_func(void *in_desc, unsigned char **buf) {
    *buf = (unsigned char *)in_desc;
    return 32768;
}

static int my_out_func(void *out_desc, unsigned char *buf, unsigned len) {
    return 0;
}

int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    z_stream strm;
    int ret;

    if (Size < 1) return 0;

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.next_in = (Bytef *)Data;
    strm.avail_in = Size;

    ret = inflateInit2_(&strm, 15, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) return 0;

    ret = inflate(&strm, Z_NO_FLUSH);
    if (ret != Z_STREAM_END && ret != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    ret = inflateEnd(&strm);
    if (ret != Z_OK) return 0;

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.next_in = (Bytef *)Data;
    strm.avail_in = Size;

    ret = inflateBackInit_(&strm, 15, window, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) return 0;

    ret = inflateBack(&strm, (in_func)my_in_func, (void *)Data, (out_func)my_out_func, NULL);
    if (ret != Z_STREAM_END && ret != Z_OK) {
        inflateBackEnd(&strm);
        return 0;
    }

    ret = inflateBackEnd(&strm);
    if (ret != Z_OK) return 0;

    return 0;
}