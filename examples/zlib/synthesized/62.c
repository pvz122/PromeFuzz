// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit_ at deflate.c:371:13 in zlib.h
// deflateTune at deflate.c:805:13 in zlib.h
// deflateResetKeep at deflate.c:635:13 in zlib.h
// deflateReset at deflate.c:695:13 in zlib.h
// deflateSetHeader at deflate.c:705:13 in zlib.h
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
    strm->next_out = Z_NULL;
    strm->avail_out = 0;
}

int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size) {
    z_stream strm;
    z_stream strm_copy;
    gz_header header;

    initialize_z_stream(&strm);
    initialize_z_stream(&strm_copy);

    if (Size < 5) return 0;

    int level = Data[0] % 10;
    int good_length = Data[1] % 256;
    int max_lazy = Data[2] % 256;
    int nice_length = Data[3] % 256;
    int max_chain = Data[4] % 256;

    deflateInit_(&strm, level, ZLIB_VERSION, sizeof(z_stream));

    deflateTune(&strm, good_length, max_lazy, nice_length, max_chain);

    deflateResetKeep(&strm);

    deflateReset(&strm);

    memset(&header, 0, sizeof(gz_header));
    deflateSetHeader(&strm, &header);

    deflateCopy(&strm_copy, &strm);

    deflateEnd(&strm);
    deflateEnd(&strm_copy);

    return 0;
}