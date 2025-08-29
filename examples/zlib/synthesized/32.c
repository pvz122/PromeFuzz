// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// adler32 at adler32.c:128:15 in zlib.h
// adler32 at adler32.c:128:15 in zlib.h
// adler32 at adler32.c:128:15 in zlib.h
// adler32 at adler32.c:128:15 in zlib.h
// adler32_combine at adler32.c:158:15 in zlib.h
// crc32 at crc32.c:1015:23 in zlib.h
// crc32 at crc32.c:1015:23 in zlib.h
// crc32 at crc32.c:1015:23 in zlib.h
// crc32_combine_gen at crc32.c:1042:15 in zlib.h
// crc32_combine_op at crc32.c:1047:15 in zlib.h
// adler32_z at adler32.c:61:15 in zlib.h
// crc32_z at crc32.c:694:23 in zlib.h
// crc32 at crc32.c:1015:23 in zlib.h
// crc32 at crc32.c:1015:23 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // adler32
    uLong adler1 = adler32(0L, Z_NULL, 0);
    uLong adler2 = adler32(adler1, Data, Size);

    // adler32_combine
    uLong adler3 = adler32(0L, Data, Size / 2);
    uLong adler4 = adler32(0L, Data + Size / 2, Size - Size / 2);
    uLong combined_adler = adler32_combine(adler3, adler4, Size - Size / 2);

    // crc32_combine_op
    uLong crc1 = crc32(0L, Z_NULL, 0);
    uLong crc2 = crc32(crc1, Data, Size / 2);
    uLong crc3 = crc32(crc2, Data + Size / 2, Size - Size / 2);
    uLong op = crc32_combine_gen(Size - Size / 2);
    uLong combined_crc = crc32_combine_op(crc2, crc3, op);

    // adler32_z
    uLong adler5 = adler32_z(0L, Data, Size);

    // crc32_z
    uLong crc4 = crc32_z(0L, Data, Size);

    // crc32
    uLong crc5 = crc32(0L, Z_NULL, 0);
    uLong crc6 = crc32(crc5, Data, Size);

    return 0;
}