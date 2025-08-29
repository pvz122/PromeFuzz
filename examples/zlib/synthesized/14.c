// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit2_ at inflate.c:178:13 in zlib.h
// inflate at inflate.c:590:13 in zlib.h
// inflateEnd at inflate.c:1266:13 in zlib.h
// crc32 at crc32.c:1015:23 in zlib.h
// crc32 at crc32.c:1015:23 in zlib.h
// crc32_combine at crc32.c:1029:15 in zlib.h
// inflateReset at inflate.c:130:13 in zlib.h
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

static void initialize_z_stream(z_streamp strm) {
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
    strm->next_in = Z_NULL;
    strm->avail_in = 0;
}

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    z_stream strm;
    int windowBits = 15;
    int flush = Z_NO_FLUSH;
    int ret;

    initialize_z_stream(&strm);

    ret = inflateInit2_(&strm, windowBits, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) {
        return 0;
    }

    strm.next_in = (Bytef *)Data;
    strm.avail_in = (uInt)Size;

    Bytef out[1024];
    strm.next_out = out;
    strm.avail_out = sizeof(out);

    ret = inflate(&strm, flush);
    if (ret != Z_OK && ret != Z_STREAM_END) {
        inflateEnd(&strm);
        return 0;
    }

    uLong crc1 = crc32(0L, Z_NULL, 0);
    uLong crc2 = crc32(0L, Data, Size);
    uLong combined_crc = crc32_combine(crc1, crc2, Size);

    ret = inflateReset(&strm);
    if (ret != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    ret = inflateEnd(&strm);
    if (ret != Z_OK) {
        return 0;
    }

    return 0;
}