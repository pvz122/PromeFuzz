// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// compressBound at compress.c:72:15 in zlib.h
// compress at compress.c:63:13 in zlib.h
// compress2 at compress.c:22:13 in zlib.h
// uncompress at uncompr.c:82:13 in zlib.h
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

int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Allocate buffers
    uLongf destLen = compressBound(Size);
    Bytef *dest = (Bytef *)malloc(destLen);
    Bytef *source = (Bytef *)malloc(Size);
    if (!dest || !source) {
        free(dest);
        free(source);
        return 0;
    }
    memcpy(source, Data, Size);

    // Test compress
    compress(dest, &destLen, source, Size);

    // Test compress2 with different compression levels
    for (int level = 0; level <= 9; ++level) {
        compress2(dest, &destLen, source, Size, level);
    }

    // Test uncompress and uncompress2
    uLongf uncompressedLen = Size * 2;
    Bytef *uncompressed = (Bytef *)malloc(uncompressedLen);
    if (uncompressed) {
        uncompress(uncompressed, &uncompressedLen, dest, destLen);
        uLongf sourceLen = destLen;
        uncompress2(uncompressed, &uncompressedLen, dest, &sourceLen);
        free(uncompressed);
    }

    // Test deflateInit2_
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    deflateInit2_(&strm, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 15, 8, Z_DEFAULT_STRATEGY, ZLIB_VERSION, sizeof(z_stream));

    // Cleanup
    free(dest);
    free(source);
    deflateEnd(&strm);

    return 0;
}