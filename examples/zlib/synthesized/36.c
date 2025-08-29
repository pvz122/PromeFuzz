// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// crc32_combine_gen at crc32.c:1042:15 in zlib.h
// adler32_combine at adler32.c:158:15 in zlib.h
// crc32_combine_op at crc32.c:1047:15 in zlib.h
// crc32_combine at crc32.c:1029:15 in zlib.h
// crc32_combine at crc32.c:1029:15 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uLong) * 4 + sizeof(z_off_t) * 2) {
        return 0;
    }

    uLong crc1 = *(uLong *)Data;
    uLong crc2 = *(uLong *)(Data + sizeof(uLong));
    uLong crc3 = *(uLong *)(Data + sizeof(uLong) * 2);
    uLong crc4 = *(uLong *)(Data + sizeof(uLong) * 3);
    z_off_t len1 = *(z_off_t *)(Data + sizeof(uLong) * 4);
    z_off_t len2 = *(z_off_t *)(Data + sizeof(uLong) * 4 + sizeof(z_off_t));

    uLong op = crc32_combine_gen(len1);
    adler32_combine(crc1, crc2, len1);
    crc32_combine_op(crc1, crc2, op);
    crc32_combine(crc1, crc2, len1);
    crc32_combine(crc3, crc4, len2);

    return 0;
}