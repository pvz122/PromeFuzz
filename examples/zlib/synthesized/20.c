// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit2_ at inflate.c:178:13 in zlib.h
// inflatePrime at inflate.c:223:13 in zlib.h
// inflateGetHeader at inflate.c:1330:13 in zlib.h
// inflate at inflate.c:590:13 in zlib.h
// inflateSetDictionary at inflate.c:1298:13 in zlib.h
// inflateSync at inflate.c:1375:13 in zlib.h
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

static void initialize_z_stream(z_streamp strm) {
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
    strm->next_in = Z_NULL;
    strm->avail_in = 0;
}

int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    z_stream strm;
    gz_header head;
    int ret;
    Bytef out[1024];

    initialize_z_stream(&strm);
    ret = inflateInit2_(&strm, MAX_WBITS, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) {
        return 0;
    }

    strm.next_in = (Bytef *)Data;
    strm.avail_in = Size;
    strm.next_out = out;
    strm.avail_out = sizeof(out);

    inflatePrime(&strm, 8, 0);
    inflateGetHeader(&strm, &head);

    while (strm.avail_in > 0) {
        ret = inflate(&strm, Z_NO_FLUSH);
        if (ret == Z_NEED_DICT) {
            inflateSetDictionary(&strm, Data, Size);
        } else if (ret == Z_DATA_ERROR) {
            inflateSync(&strm);
        } else if (ret != Z_OK && ret != Z_STREAM_END) {
            break;
        }
    }

    inflateEnd(&strm);
    return 0;
}