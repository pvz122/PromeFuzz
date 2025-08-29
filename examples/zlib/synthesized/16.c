// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit_ at deflate.c:371:13 in zlib.h
// deflate at deflate.c:954:13 in zlib.h
// deflateParams at deflate.c:760:13 in zlib.h
// deflate at deflate.c:954:13 in zlib.h
// deflateParams at deflate.c:760:13 in zlib.h
// deflate at deflate.c:954:13 in zlib.h
// deflate at deflate.c:954:13 in zlib.h
// deflateEnd at deflate.c:1266:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    z_stream strm;
    int ret;
    Bytef in[Size];
    Bytef out[1024];

    if (Size < 1) return 0;

    memcpy(in, Data, Size);

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.next_in = in;
    strm.avail_in = Size;
    strm.next_out = out;
    strm.avail_out = sizeof(out);

    ret = deflateInit_(&strm, Z_DEFAULT_COMPRESSION, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) return 0;

    ret = deflate(&strm, Z_NO_FLUSH);
    if (ret != Z_OK && ret != Z_STREAM_END) goto cleanup;

    ret = deflateParams(&strm, Z_BEST_COMPRESSION, Z_DEFAULT_STRATEGY);
    if (ret != Z_OK) goto cleanup;

    ret = deflate(&strm, Z_FULL_FLUSH);
    if (ret != Z_OK && ret != Z_STREAM_END) goto cleanup;

    ret = deflateParams(&strm, Z_BEST_SPEED, Z_DEFAULT_STRATEGY);
    if (ret != Z_OK) goto cleanup;

    ret = deflate(&strm, Z_FINISH);
    if (ret != Z_OK && ret != Z_STREAM_END) goto cleanup;

    ret = deflate(&strm, Z_NO_FLUSH);
    if (ret != Z_OK && ret != Z_STREAM_END) goto cleanup;

cleanup:
    deflateEnd(&strm);
    return 0;
}