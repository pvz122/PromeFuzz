// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// crc32_combine64 at crc32.c:1021:15 in zlib.h
// crc32_combine_gen64 at crc32.c:1034:15 in zlib.h
// crc32_combine_op at crc32.c:1047:15 in zlib.h
// crc32_combine at crc32.c:1029:15 in zlib.h
// adler32_combine64 at adler32.c:162:15 in zlib.h
// crc32_combine_gen at crc32.c:1042:15 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uLong) * 4 + sizeof(z_off_t) + sizeof(z_off64_t)) {
        return 0;
    }

    uLong crc1 = *(uLong *)Data;
    uLong crc2 = *(uLong *)(Data + sizeof(uLong));
    z_off_t len2 = *(z_off_t *)(Data + sizeof(uLong) * 2);
    z_off64_t len2_64 = *(z_off64_t *)(Data + sizeof(uLong) * 2 + sizeof(z_off_t));
    uLong op = *(uLong *)(Data + sizeof(uLong) * 2 + sizeof(z_off_t) + sizeof(z_off64_t));

    crc32_combine64(crc1, crc2, len2_64);
    crc32_combine_gen64(len2_64);
    crc32_combine_op(crc1, crc2, op);
    crc32_combine(crc1, crc2, len2);
    adler32_combine64(crc1, crc2, len2_64);
    crc32_combine_gen(len2);

    return 0;
}