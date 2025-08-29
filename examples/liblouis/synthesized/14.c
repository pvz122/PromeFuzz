// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_translateString at lou_translateString.c:1117:1 in liblouis.h
// lou_translate at lou_translateString.c:1124:1 in liblouis.h
// lou_charToDots at lou_translateString.c:4154:1 in liblouis.h
// lou_backTranslate at lou_backTranslateString.c:150:1 in liblouis.h
// lou_dotsToChar at lou_translateString.c:4131:1 in liblouis.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "liblouis.h"

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    const char *tableList = "unicode.dis,en-us-g2.ctb";
    widechar inbuf[256];
    widechar outbuf[256];
    int inlen = Size > sizeof(inbuf) ? sizeof(inbuf) : Size;
    int outlen = sizeof(outbuf);
    formtype typeform[256];
    char spacing[256];
    int outputPos[256];
    int inputPos[256];
    int cursorPos = -1;
    int mode = 0;

    memcpy(inbuf, Data, inlen);

    lou_translateString(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, mode);
    lou_translate(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, mode);
    lou_charToDots(tableList, inbuf, outbuf, inlen, mode);
    lou_backTranslate(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, mode);
    lou_dotsToChar(tableList, inbuf, outbuf, inlen, mode);

    return 0;
}