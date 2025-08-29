// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit2_ at deflate.c:379:13 in zlib.h
// deflateBound at deflate.c:842:15 in zlib.h
// compressBound at compress.c:72:15 in zlib.h
// deflatePrime at deflate.c:731:13 in zlib.h
// deflateSetDictionary at deflate.c:550:13 in zlib.h
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

int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;

    int level = Data[0] % 10;
    int method = Z_DEFLATED;
    int windowBits = 15;
    int memLevel = 8;
    int strategy = Z_DEFAULT_STRATEGY;

    if (deflateInit2_(&strm, level, method, windowBits, memLevel, strategy, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    uLong sourceLen = Size - 1;
    uLong bound = deflateBound(&strm, sourceLen);
    uLong compressBoundVal = compressBound(sourceLen);

    Bytef *in = (Bytef *)(Data + 1);
    Bytef *out = (Bytef *)malloc(bound);

    strm.next_in = in;
    strm.avail_in = sourceLen;
    strm.next_out = out;
    strm.avail_out = bound;

    deflatePrime(&strm, 5, 31);

    Bytef dictionary[256];
    memcpy(dictionary, Data, Size < 256 ? Size : 256);
    deflateSetDictionary(&strm, dictionary, Size < 256 ? Size : 256);

    deflate(&strm, Z_FINISH);

    free(out);
    deflateEnd(&strm);

    return 0;
}