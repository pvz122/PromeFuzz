// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit_ at inflate.c:218:13 in zlib.h
// inflateReset at inflate.c:130:13 in zlib.h
// inflateGetDictionary at inflate.c:1278:13 in zlib.h
// inflate at inflate.c:590:13 in zlib.h
// inflateCodesUsed at inflate.c:1521:23 in zlib.h
// uncompress2 at uncompr.c:27:13 in zlib.h
// uncompress at uncompr.c:82:13 in zlib.h
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

int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    Bytef *dict = (Bytef *)malloc(32768);
    uInt dictLength = 32768;
    Bytef *dest = (Bytef *)malloc(Size * 2);
    uLongf destLen = Size * 2;
    uLong sourceLen = Size;
    int flush = Z_NO_FLUSH;

    memset(&strm, 0, sizeof(z_stream));
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = Size;
    strm.next_in = (Bytef *)Data;

    inflateInit(&strm);

    inflateReset(&strm);

    inflateGetDictionary(&strm, dict, &dictLength);

    while (strm.avail_in > 0) {
        strm.avail_out = destLen;
        strm.next_out = dest;
        inflate(&strm, flush);
    }

    inflateCodesUsed(&strm);

    uncompress2(dest, &destLen, Data, &sourceLen);

    uncompress(dest, &destLen, Data, Size);

    inflateEnd(&strm);

    free(dict);
    free(dest);

    return 0;
}