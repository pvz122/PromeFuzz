// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit2_ at inflate.c:178:13 in zlib.h
// inflateGetHeader at inflate.c:1330:13 in zlib.h
// inflateEnd at inflate.c:1266:13 in zlib.h
// inflate at inflate.c:590:13 in zlib.h
// inflateEnd at inflate.c:1266:13 in zlib.h
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

int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    z_stream strm;
    gz_header header;
    int ret;

    // Initialize zlib stream
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = Size;
    strm.next_in = (Bytef *)Data;

    ret = inflateInit2_(&strm, MAX_WBITS + 16, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) {
        return 0;
    }

    // Set up gzip header
    memset(&header, 0, sizeof(header));
    ret = inflateGetHeader(&strm, &header);
    if (ret != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    // Decompress data
    Bytef out[4096];
    strm.avail_out = sizeof(out);
    strm.next_out = out;

    ret = inflate(&strm, Z_NO_FLUSH);
    if (ret != Z_STREAM_END && ret != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    inflateEnd(&strm);
    return 0;
}