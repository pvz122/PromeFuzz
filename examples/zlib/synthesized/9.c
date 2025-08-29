// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit2_ at deflate.c:379:13 in zlib.h
// deflateEnd at deflate.c:1266:13 in zlib.h
// deflateSetDictionary at deflate.c:550:13 in zlib.h
// deflateEnd at deflate.c:1266:13 in zlib.h
// deflateEnd at deflate.c:1266:13 in zlib.h
// deflatePrime at deflate.c:731:13 in zlib.h
// deflateEnd at deflate.c:1266:13 in zlib.h
// deflate at deflate.c:954:13 in zlib.h
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

int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;

    int level = Data[0] % 10;
    int windowBits = 15;
    int memLevel = 8;
    int strategy = Z_DEFAULT_STRATEGY;

    if (deflateInit2_(&strm, level, Z_DEFLATED, windowBits, memLevel, strategy, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    deflateEnd(&strm);

    Bytef dictionary[256];
    uInt dictLength = Size > 256 ? 256 : Size;
    memcpy(dictionary, Data, dictLength);

    if (deflateSetDictionary(&strm, dictionary, dictLength) != Z_OK) {
        deflateEnd(&strm);
        return 0;
    }

    deflateEnd(&strm);

    int bits = Data[0] % 16;
    int value = Data[0];

    if (deflatePrime(&strm, bits, value) != Z_OK) {
        deflateEnd(&strm);
        return 0;
    }

    Bytef out[1024];
    strm.avail_in = Size;
    strm.next_in = (Bytef *)Data;
    strm.avail_out = sizeof(out);
    strm.next_out = out;

    int flush = Z_FINISH;
    deflate(&strm, flush);

    deflateEnd(&strm);
    deflateEnd(&strm);

    return 0;
}