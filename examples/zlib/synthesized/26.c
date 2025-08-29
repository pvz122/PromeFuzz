// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit_ at deflate.c:371:13 in zlib.h
// inflateGetDictionary at inflate.c:1278:13 in zlib.h
// deflateReset at deflate.c:695:13 in zlib.h
// deflateGetDictionary at deflate.c:616:13 in zlib.h
// deflateUsed at deflate.c:723:13 in zlib.h
// deflateSetDictionary at deflate.c:550:13 in zlib.h
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

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    Bytef dictionary[32768];
    uInt dictLength = sizeof(dictionary);
    int bits;
    int level = Data[0] % 10; // Ensure level is within valid range

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;

    if (deflateInit_(&strm, level, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    inflateGetDictionary(&strm, dictionary, &dictLength);
    deflateReset(&strm);
    deflateGetDictionary(&strm, dictionary, &dictLength);
    deflateUsed(&strm, &bits);

    if (Size > 1) {
        deflateSetDictionary(&strm, Data + 1, Size - 1);
    }

    deflateEnd(&strm);
    return 0;
}