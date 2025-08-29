// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// zlibVersion at zutil.c:27:22 in zlib.h
// zlibVersion at zutil.c:27:22 in zlib.h
// zlibVersion at zutil.c:27:22 in zlib.h
// zlibCompileFlags at zutil.c:31:15 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    (void)Data;
    (void)Size;

    // Call zlibVersion three times
    const char *version1 = zlibVersion();
    const char *version2 = zlibVersion();
    const char *version3 = zlibVersion();

    // Call zlibCompileFlags
    uLong flags = zlibCompileFlags();

    return 0;
}