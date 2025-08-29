// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_translatePrehyphenated at lou_translateString.c:1399:1 in liblouis.h
// lou_hyphenate at lou_translateString.c:4047:1 in liblouis.h
// lou_readCharFromFile at compileTranslationTable.c:4332:1 in liblouis.h
// lou_dotsToChar at lou_translateString.c:4131:1 in liblouis.h
// lou_charSize at compileTranslationTable.c:5388:1 in liblouis.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "liblouis.h"

int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare variables for lou_translatePrehyphenated
    const char *tableList = "en-us-g2.ctb";
    widechar inbuf[256];
    int inlen = Size > 256 ? 256 : Size;
    widechar outbuf[256];
    int outlen = 256;
    formtype typeform[256];
    char spacing[256];
    int outputPos[256];
    int inputPos[256];
    int cursorPos = 0;
    char inputHyphens[256];
    char outputHyphens[256];
    int mode = 0;

    memcpy(inbuf, Data, inlen);
    lou_translatePrehyphenated(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, inputHyphens, outputHyphens, mode);

    // Prepare variables for lou_hyphenate
    char hyphens[256];
    lou_hyphenate(tableList, inbuf, inlen, hyphens, mode);

    // Prepare variables for lou_readCharFromFile
    FILE *fp = fopen("./dummy_file", "wb");
    if (fp) {
        fwrite(Data, 1, Size, fp);
        fclose(fp);
    }
    int readMode = 1;
    lou_readCharFromFile("./dummy_file", &readMode);

    // Prepare variables for lou_dotsToChar
    widechar dotsInbuf[256];
    widechar dotsOutbuf[256];
    int length = Size > 256 ? 256 : Size;
    memcpy(dotsInbuf, Data, length);
    lou_dotsToChar(tableList, dotsInbuf, dotsOutbuf, length, mode);

    // Call lou_charSize
    lou_charSize();

    return 0;
}