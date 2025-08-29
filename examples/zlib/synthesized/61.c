// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// deflateInit_ at deflate.c:371:13 in zlib.h
// deflateTune at deflate.c:805:13 in zlib.h
// deflateSetHeader at deflate.c:705:13 in zlib.h
// deflateResetKeep at deflate.c:635:13 in zlib.h
// deflateReset at deflate.c:695:13 in zlib.h
// deflateCopy at deflate.c:1290:13 in zlib.h
// deflateReset at deflate.c:695:13 in zlib.h
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

static void initialize_gz_header(gz_headerp head) {
    head->text = 0;
    head->time = 0;
    head->xflags = 0;
    head->os = 0;
    head->extra = Z_NULL;
    head->extra_len = 0;
    head->extra_max = 0;
    head->name = Z_NULL;
    head->name_max = 0;
    head->comment = Z_NULL;
    head->comm_max = 0;
    head->hcrc = 0;
    head->done = 0;
}

int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size) {
    if (Size < 5) return 0;

    z_stream strm1, strm2;
    gz_header head;
    int level = Data[0] % 10;
    int good_length = Data[1] % 256;
    int max_lazy = Data[2] % 256;
    int nice_length = Data[3] % 256;
    int max_chain = Data[4] % 256;

    initialize_z_stream(&strm1);
    initialize_z_stream(&strm2);
    initialize_gz_header(&head);

    if (deflateInit_(&strm1, level, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    deflateTune(&strm1, good_length, max_lazy, nice_length, max_chain);
    deflateSetHeader(&strm1, &head);
    deflateResetKeep(&strm1);
    deflateReset(&strm1);

    if (deflateCopy(&strm2, &strm1) == Z_OK) {
        deflateReset(&strm2);
    }

    deflateEnd(&strm1);
    deflateEnd(&strm2);

    return 0;
}