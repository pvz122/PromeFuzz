// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// crc32_combine_gen at crc32.c:1042:15 in zlib.h
// adler32_combine at adler32.c:158:15 in zlib.h
// crc32_combine at crc32.c:1029:15 in zlib.h
// crc32_combine_op at crc32.c:1047:15 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < 4 * sizeof(uLong) + 2 * sizeof(z_off_t)) {
        return 0;
    }

    uLong adler1 = *(uLong *)Data;
    uLong adler2 = *(uLong *)(Data + sizeof(uLong));
    z_off_t len1 = *(z_off_t *)(Data + 2 * sizeof(uLong));

    uLong crc1 = *(uLong *)(Data + 2 * sizeof(uLong) + sizeof(z_off_t));
    uLong crc2 = *(uLong *)(Data + 3 * sizeof(uLong) + sizeof(z_off_t));
    z_off_t len2 = *(z_off_t *)(Data + 4 * sizeof(uLong) + sizeof(z_off_t));

    uLong op = crc32_combine_gen(len2);

    adler32_combine(adler1, adler2, len1);
    crc32_combine(crc1, crc2, len2);
    crc32_combine_op(crc1, crc2, op);

    return 0;
}