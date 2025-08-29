// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_registerLogCallback at logging.c:85:1 in liblouis.h
// lou_checkTable at compileTranslationTable.c:5202:1 in liblouis.h
// lou_free at compileTranslationTable.c:5327:1 in liblouis.h
// lou_free at compileTranslationTable.c:5327:1 in liblouis.h
// lou_backTranslateString at lou_backTranslateString.c:143:1 in liblouis.h
// lou_free at compileTranslationTable.c:5327:1 in liblouis.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "liblouis.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void dummyLogCallback(logLevels level, const char *message) {
    // Do nothing
}

int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    lou_registerLogCallback(dummyLogCallback);

    const char *tableList = "en-us-g2.ctb";
    lou_checkTable(tableList);

    lou_free();
    lou_free();

    widechar inbuf[Size];
    widechar outbuf[Size];
    formtype typeform[Size];
    char spacing[Size];
    int inlen = Size;
    int outlen = Size;
    int mode = 0;

    for (size_t i = 0; i < Size; ++i) {
        inbuf[i] = Data[i];
        typeform[i] = 0;
        spacing[i] = 0;
    }

    lou_backTranslateString(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, mode);

    lou_free();

    return 0;
}