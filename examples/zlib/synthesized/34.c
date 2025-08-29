// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// crc32_combine_gen at crc32.c:1042:15 in zlib.h
// adler32_combine at adler32.c:158:15 in zlib.h
// crc32_combine_gen at crc32.c:1042:15 in zlib.h
// crc32_combine_op at crc32.c:1047:15 in zlib.h
// crc32_combine at crc32.c:1029:15 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uLong) * 2 + sizeof(z_off_t)) {
        return 0;
    }

    uLong crc1 = *((uLong *)Data);
    uLong crc2 = *((uLong *)(Data + sizeof(uLong)));
    z_off_t len2 = *((z_off_t *)(Data + sizeof(uLong) * 2));

    // Fuzz crc32_combine_gen
    uLong gen = crc32_combine_gen(len2);

    // Fuzz adler32_combine
    uLong adler_combined = adler32_combine(crc1, crc2, len2);

    // Fuzz crc32_combine_op
    uLong op = crc32_combine_gen(len2);
    uLong crc_combined_op = crc32_combine_op(crc1, crc2, op);

    // Fuzz crc32_combine
    uLong crc_combined = crc32_combine(crc1, crc2, len2);

    return 0;
}