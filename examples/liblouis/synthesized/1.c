// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_registerLogCallback at logging.c:85:1 in liblouis.h
// lou_checkTable at compileTranslationTable.c:5202:1 in liblouis.h
// lou_free at compileTranslationTable.c:5327:1 in liblouis.h
// lou_free at compileTranslationTable.c:5327:1 in liblouis.h
// lou_translateString at lou_translateString.c:1117:1 in liblouis.h
// lou_free at compileTranslationTable.c:5327:1 in liblouis.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <liblouis.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void logCallback(logLevels level, const char *message) {
    // Do nothing with the log message
}

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    lou_registerLogCallback(logCallback);

    const char *tableList = "en-us-g2.ctb";
    lou_checkTable(tableList);

    lou_free();
    lou_free();

    widechar *inbuf = (widechar *)Data;
    int inlen = Size / sizeof(widechar);
    widechar outbuf[1024];
    int outlen = sizeof(outbuf) / sizeof(widechar);
    formtype *typeform = NULL;
    char *spacing = NULL;
    int mode = 0;

    lou_translateString(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, mode);

    lou_free();

    return 0;
}