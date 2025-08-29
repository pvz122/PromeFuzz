// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// bitstr_putc at bitstr.c:209:5 in bitstr.h
// bitstr_getb at bitstr.c:245:5 in bitstr.h
// bitstr_putb at bitstr.c:273:5 in bitstr.h
// bitstr_get_bits at bitstr.c:299:5 in bitstr.h
// bitstr_put_bits at bitstr.c:309:5 in bitstr.h
// bitstr_flush at bitstr.c:321:5 in bitstr.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "bitstr.h"

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a dummy stream
    FILE *stream = fopen("./dummy_file", "wb+");
    if (!stream) return 0;

    // Use the first byte to determine the operation
    uint8_t operation = Data[0] % 6;
    Data++;
    Size--;

    switch (operation) {
        case 0: {
            if (Size < sizeof(int) * 2) break;
            int bits = *(int *)Data;
            int n = *(int *)(Data + sizeof(int));
            bitstr_put_bits(stream, bits, n);
            break;
        }
        case 1: {
            if (Size < 1) break;
            int b = Data[0] & 1;
            bitstr_putb(b, stream);
            break;
        }
        case 2: {
            if (Size < 1) break;
            int c = Data[0];
            bitstr_putc(c, stream);
            break;
        }
        case 3: {
            if (Size < 1) break;
            int flag = Data[0] & 1;
            bitstr_flush(stream, flag);
            break;
        }
        case 4: {
            bitstr_getb(stream);
            break;
        }
        case 5: {
            if (Size < sizeof(int)) break;
            int n = *(int *)Data;
            bitstr_get_bits(stream, n);
            break;
        }
    }

    fclose(stream);
    return 0;
}