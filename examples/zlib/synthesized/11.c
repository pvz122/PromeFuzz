// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// crc32 at crc32.c:1015:23 in zlib.h
// crc32 at crc32.c:1015:23 in zlib.h
// deflateInit2_ at deflate.c:379:13 in zlib.h
// deflateSetDictionary at deflate.c:550:13 in zlib.h
// deflateEnd at deflate.c:1266:13 in zlib.h
// deflatePrime at deflate.c:731:13 in zlib.h
// deflateEnd at deflate.c:1266:13 in zlib.h
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

int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    uLong crc = crc32(0L, Z_NULL, 0);
    crc = crc32(crc, Data, Size);

    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;

    int ret = deflateInit2_(&strm, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 15, 8, Z_DEFAULT_STRATEGY, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) return 0;

    Bytef dictionary[256];
    memcpy(dictionary, Data, Size < 256 ? Size : 256);
    ret = deflateSetDictionary(&strm, dictionary, Size < 256 ? Size : 256);
    if (ret != Z_OK) {
        deflateEnd(&strm);
        return 0;
    }

    ret = deflatePrime(&strm, 5, 31);
    if (ret != Z_OK && ret != Z_BUF_ERROR && ret != Z_STREAM_ERROR) {
        deflateEnd(&strm);
        return 0;
    }

    deflateEnd(&strm);
    return 0;
}