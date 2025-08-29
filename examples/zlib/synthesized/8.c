// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit2_ at inflate.c:178:13 in zlib.h
// inflateReset2 at inflate.c:141:13 in zlib.h
// inflatePrime at inflate.c:223:13 in zlib.h
// inflateSetDictionary at inflate.c:1298:13 in zlib.h
// inflate at inflate.c:590:13 in zlib.h
// inflateReset2 at inflate.c:141:13 in zlib.h
// inflate at inflate.c:590:13 in zlib.h
// inflateReset2 at inflate.c:141:13 in zlib.h
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

static void init_z_stream(z_streamp strm) {
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
    strm->next_in = Z_NULL;
    strm->avail_in = 0;
    inflateInit2(strm, 15);
}

int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    z_stream strm;
    init_z_stream(&strm);

    Bytef *out = (Bytef *)malloc(Size * 2);
    if (!out) return 0;

    strm.next_in = (Bytef *)Data;
    strm.avail_in = (uInt)Size;
    strm.next_out = out;
    strm.avail_out = (uInt)(Size * 2);

    inflateReset2(&strm, 15);
    inflatePrime(&strm, 8, 0);
    
    Bytef dictionary[256];
    memset(dictionary, 0, sizeof(dictionary));
    inflateSetDictionary(&strm, dictionary, sizeof(dictionary));

    inflate(&strm, Z_NO_FLUSH);
    inflateReset2(&strm, 15);
    inflate(&strm, Z_FINISH);
    inflateReset2(&strm, 15);

    free(out);
    inflateEnd(&strm);
    return 0;
}