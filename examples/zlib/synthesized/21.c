// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit2_ at inflate.c:178:13 in zlib.h
// inflatePrime at inflate.c:223:13 in zlib.h
// inflateEnd at inflate.c:1266:13 in zlib.h
// inflateReset2 at inflate.c:141:13 in zlib.h
// inflateEnd at inflate.c:1266:13 in zlib.h
// inflateBackInit_ at infback.c:25:13 in zlib.h
// inflateEnd at inflate.c:1266:13 in zlib.h
// inflateBack at infback.c:242:13 in zlib.h
// inflateBackEnd at infback.c:621:13 in zlib.h
// inflateEnd at inflate.c:1266:13 in zlib.h
// inflateBackEnd at infback.c:621:13 in zlib.h
// inflateEnd at inflate.c:1266:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static unsigned char dummy_window[32768];

static unsigned int my_in_func(void *desc, unsigned char **buf) {
    *buf = (unsigned char *)desc;
    return 0;
}

static int my_out_func(void *desc, unsigned char *buf, unsigned int len) {
    return 0;
}

int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    z_stream strm;
    int ret;

    if (Size < 1) return 0;

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.next_in = (Bytef *)Data;
    strm.avail_in = Size;

    ret = inflateInit2(&strm, 15 + 16);
    if (ret != Z_OK) return 0;

    ret = inflatePrime(&strm, 8, Data[0]);
    if (ret != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    ret = inflateReset2(&strm, 15 + 16);
    if (ret != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    ret = inflateBackInit_(&strm, 15, dummy_window, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    ret = inflateBack(&strm, (in_func)my_in_func, (void *)Data, (out_func)my_out_func, NULL);
    if (ret != Z_STREAM_END && ret != Z_OK) {
        inflateBackEnd(&strm);
        inflateEnd(&strm);
        return 0;
    }

    inflateBackEnd(&strm);
    inflateEnd(&strm);

    return 0;
}