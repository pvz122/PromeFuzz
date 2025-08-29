// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_translate at lou_translateString.c:1124:1 in liblouis.h
// lou_translate at lou_translateString.c:1124:1 in liblouis.h
// lou_charToDots at lou_translateString.c:4154:1 in liblouis.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <liblouis.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    const char *tableList = "en-us-g2.ctb";
    widechar inbuf[256];
    widechar outbuf[256];
    int inlen = Size > 256 ? 256 : Size;
    int outlen = 256;
    formtype typeform[256] = {0};
    char spacing[256] = {0};
    int outputPos[256] = {0};
    int inputPos[256] = {0};
    int cursorPos = -1;
    int mode = 0;

    memcpy(inbuf, Data, inlen);

    lou_translate(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, mode);
    lou_translate(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, mode);
    lou_charToDots(tableList, inbuf, outbuf, inlen, mode);

    return 0;
}