// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit_ at deflate.c:371:13 in zlib.h
// deflateResetKeep at deflate.c:635:13 in zlib.h
// deflateReset at deflate.c:695:13 in zlib.h
// deflateUsed at deflate.c:723:13 in zlib.h
// deflateTune at deflate.c:805:13 in zlib.h
// deflateCopy at deflate.c:1290:13 in zlib.h
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

static void initialize_z_stream(z_streamp strm) {
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
    strm->next_in = Z_NULL;
    strm->avail_in = 0;
}

int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    z_stream strm;
    int ret;
    int bits;
    z_stream dest_strm;

    initialize_z_stream(&strm);

    ret = deflateInit_(&strm, Z_DEFAULT_COMPRESSION, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) {
        return 0;
    }

    strm.next_in = (Bytef *)Data;
    strm.avail_in = (uInt)Size;

    deflateResetKeep(&strm);
    deflateReset(&strm);

    deflateUsed(&strm, &bits);

    deflateTune(&strm, 8, 16, 32, 64);

    deflateCopy(&dest_strm, &strm);

    deflateEnd(&strm);
    deflateEnd(&dest_strm);

    return 0;
}