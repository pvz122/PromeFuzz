// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit2_ at inflate.c:178:13 in zlib.h
// inflatePrime at inflate.c:223:13 in zlib.h
// inflateBackInit_ at infback.c:25:13 in zlib.h
// inflateReset2 at inflate.c:141:13 in zlib.h
// inflateBack at infback.c:242:13 in zlib.h
// inflateBackEnd at infback.c:621:13 in zlib.h
// inflate at inflate.c:590:13 in zlib.h
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

static unsigned char dummy_window[1 << 15];

static unsigned int dummy_in_func(void *desc, unsigned char **buf) {
    *buf = (unsigned char *)desc;
    return 0;
}

static int dummy_out_func(void *desc, unsigned char *buf, unsigned int len) {
    return 0;
}

int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    z_stream strm;
    int ret;

    if (Size < 1) return 0;

    // Initialize z_stream
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.next_in = Z_NULL;
    strm.avail_in = 0;

    ret = inflateInit2(&strm, MAX_WBITS);
    if (ret != Z_OK) return 0;

    // Fuzz inflatePrime
    inflatePrime(&strm, Data[0] % 16, Data[0]);

    // Fuzz inflateBackInit_
    inflateBackInit_(&strm, MAX_WBITS, dummy_window, ZLIB_VERSION, sizeof(z_stream));

    // Fuzz inflateReset2
    inflateReset2(&strm, MAX_WBITS);

    // Fuzz inflateBack
    inflateBack(&strm, dummy_in_func, (void *)Data, dummy_out_func, NULL);

    // Fuzz inflateBackEnd
    inflateBackEnd(&strm);

    // Fuzz inflate
    strm.next_in = (Bytef *)Data;
    strm.avail_in = Size;
    strm.next_out = dummy_window;
    strm.avail_out = sizeof(dummy_window);

    inflate(&strm, Z_NO_FLUSH);

    inflateEnd(&strm);

    return 0;
}