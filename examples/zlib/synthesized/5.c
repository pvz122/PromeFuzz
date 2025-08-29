// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit_ at deflate.c:371:13 in zlib.h
// deflateEnd at deflate.c:1266:13 in zlib.h
// inflateInit_ at inflate.c:218:13 in zlib.h
// deflateReset at deflate.c:695:13 in zlib.h
// inflateEnd at inflate.c:1266:13 in zlib.h
// inflateReset at inflate.c:130:13 in zlib.h
// inflateEnd at inflate.c:1266:13 in zlib.h
// deflateReset at deflate.c:695:13 in zlib.h
// inflateEnd at inflate.c:1266:13 in zlib.h
// inflateEnd at inflate.c:1266:13 in zlib.h
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

static void initialize_z_stream(z_streamp strm) {
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
    strm->next_in = Z_NULL;
    strm->avail_in = 0;
}

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    z_stream deflate_stream;
    z_stream inflate_stream;

    initialize_z_stream(&deflate_stream);
    initialize_z_stream(&inflate_stream);

    if (deflateInit_(&deflate_stream, Z_DEFAULT_COMPRESSION, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    if (deflateEnd(&deflate_stream) != Z_OK) {
        return 0;
    }

    if (inflateInit_(&inflate_stream, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    if (deflateReset(&deflate_stream) != Z_OK) {
        inflateEnd(&inflate_stream);
        return 0;
    }

    if (inflateReset(&inflate_stream) != Z_OK) {
        inflateEnd(&inflate_stream);
        return 0;
    }

    if (deflateReset(&deflate_stream) != Z_OK) {
        inflateEnd(&inflate_stream);
        return 0;
    }

    if (inflateEnd(&inflate_stream) != Z_OK) {
        return 0;
    }

    if (deflateEnd(&deflate_stream) != Z_OK) {
        return 0;
    }

    return 0;
}