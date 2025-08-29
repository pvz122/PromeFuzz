// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// crc32 at crc32.c:1015:23 in zlib.h
// crc32 at crc32.c:1015:23 in zlib.h
// crc32_combine64 at crc32.c:1021:15 in zlib.h
// get_crc_table at crc32.c:549:29 in zlib.h
// crc32_combine at crc32.c:1029:15 in zlib.h
// crc32_z at crc32.c:694:23 in zlib.h
// crc32_z at crc32.c:694:23 in zlib.h
// crc32_combine_gen64 at crc32.c:1034:15 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <zlib.h>

static void fuzz_crc32(const uint8_t *Data, size_t Size) {
    uLong crc = crc32(0L, Z_NULL, 0);
    crc = crc32(crc, Data, (uInt)Size);
}

static void fuzz_crc32_combine64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uLong) * 2 + sizeof(z_off64_t)) return;
    uLong crc1 = *(const uLong *)Data;
    uLong crc2 = *(const uLong *)(Data + sizeof(uLong));
    z_off64_t len2 = *(const z_off64_t *)(Data + sizeof(uLong) * 2);
    crc32_combine64(crc1, crc2, len2);
}

static void fuzz_get_crc_table(void) {
    const z_crc_t FAR *table = get_crc_table();
    (void)table; // Suppress unused variable warning
}

static void fuzz_crc32_combine(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uLong) * 2 + sizeof(z_off_t)) return;
    uLong crc1 = *(const uLong *)Data;
    uLong crc2 = *(const uLong *)(Data + sizeof(uLong));
    z_off_t len2 = *(const z_off_t *)(Data + sizeof(uLong) * 2);
    crc32_combine(crc1, crc2, len2);
}

static void fuzz_crc32_z(const uint8_t *Data, size_t Size) {
    uLong crc = crc32_z(0L, Z_NULL, 0);
    crc = crc32_z(crc, Data, (z_size_t)Size);
}

static void fuzz_crc32_combine_gen64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(z_off64_t)) return;
    z_off64_t len2 = *(const z_off64_t *)Data;
    crc32_combine_gen64(len2);
}

int LLVMFuzzerTestOneInput_72(const uint8_t *Data, size_t Size) {
    fuzz_crc32(Data, Size);
    fuzz_crc32_combine64(Data, Size);
    fuzz_get_crc_table();
    fuzz_crc32_combine(Data, Size);
    fuzz_crc32_z(Data, Size);
    fuzz_crc32_combine_gen64(Data, Size);
    return 0;
}