// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// compressBound at compress.c:72:15 in zlib.h
// compress at compress.c:63:13 in zlib.h
// uncompress at uncompr.c:82:13 in zlib.h
// compress2 at compress.c:22:13 in zlib.h
// uncompress2 at uncompr.c:27:13 in zlib.h
// deflateInit2_ at deflate.c:379:13 in zlib.h
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

int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Allocate memory for compressed and decompressed data
    uLongf destLen = compressBound(Size);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (!dest) return 0;

    Bytef *decompressed = (Bytef *)malloc(Size);
    if (!decompressed) {
        free(dest);
        return 0;
    }

    // Test compress
    int ret = compress(dest, &destLen, Data, Size);
    if (ret != Z_OK) {
        free(dest);
        free(decompressed);
        return 0;
    }

    // Test uncompress
    uLongf decompressedLen = Size;
    ret = uncompress(decompressed, &decompressedLen, dest, destLen);
    if (ret != Z_OK) {
        free(dest);
        free(decompressed);
        return 0;
    }

    // Test compress2
    int level = Data[0] % 10; // Random level between 0 and 9
    ret = compress2(dest, &destLen, Data, Size, level);
    if (ret != Z_OK) {
        free(dest);
        free(decompressed);
        return 0;
    }

    // Test uncompress2
    uLongf sourceLen = destLen;
    ret = uncompress2(decompressed, &decompressedLen, dest, &sourceLen);
    if (ret != Z_OK) {
        free(dest);
        free(decompressed);
        return 0;
    }

    // Test deflateInit2_
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit2_(&strm, level, Z_DEFLATED, MAX_WBITS, MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) {
        free(dest);
        free(decompressed);
        return 0;
    }
    deflateEnd(&strm);

    free(dest);
    free(decompressed);

    return 0;
}