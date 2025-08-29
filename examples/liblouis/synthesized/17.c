// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_readCharFromFile at compileTranslationTable.c:4332:1 in liblouis.h
// lou_translateString at lou_translateString.c:1117:1 in liblouis.h
// lou_compileString at compileTranslationTable.c:5393:1 in liblouis.h
// lou_charToDots at lou_translateString.c:4154:1 in liblouis.h
// lou_backTranslate at lou_backTranslateString.c:150:1 in liblouis.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liblouis.h"

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare dummy file for lou_readCharFromFile
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Test lou_readCharFromFile
    int mode = 1;
    file = fopen("./dummy_file", "rb");
    if (file) {
        while (lou_readCharFromFile("./dummy_file", &mode) != EOF);
        fclose(file);
    }

    // Test lou_translateString
    widechar inbuf[256], outbuf[256];
    int inlen = Size > 256 ? 256 : Size;
    int outlen = 256;
    memcpy(inbuf, Data, inlen);
    lou_translateString("en-us-g2.ctb", inbuf, &inlen, outbuf, &outlen, NULL, NULL, 0);

    // Test lou_compileString
    char inString[256];
    memcpy(inString, Data, Size > 255 ? 255 : Size);
    inString[Size > 255 ? 255 : Size] = '\0';
    lou_compileString("en-us-g2.ctb", inString);

    // Test lou_charToDots
    lou_charToDots("en-us-g2.ctb", inbuf, outbuf, inlen, 0);

    // Test lou_backTranslate
    int outputPos[256], inputPos[256], cursorPos = 0;
    lou_backTranslate("en-us-g2.ctb", inbuf, &inlen, outbuf, &outlen, NULL, NULL, outputPos, inputPos, &cursorPos, 0);

    return 0;
}