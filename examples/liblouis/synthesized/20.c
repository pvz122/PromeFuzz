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
#include <liblouis.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    // Test lou_readCharFromFile
    write_dummy_file(data, size);
    int mode = 1;
    while (lou_readCharFromFile("./dummy_file", &mode) != EOF) {}

    // Test lou_translateString
    const char *tableList = "en-us-g2.ctb";
    widechar inbuf[256];
    int inlen = sizeof(inbuf) / sizeof(widechar);
    widechar outbuf[256];
    int outlen = sizeof(outbuf) / sizeof(widechar);
    formtype typeform[256];
    char spacing[256];
    memset(inbuf, 0, sizeof(inbuf));
    memcpy(inbuf, data, size < sizeof(inbuf) ? size : sizeof(inbuf));
    lou_translateString(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, 0);

    // Test lou_compileString
    char inString[256];
    memcpy(inString, data, size < sizeof(inString) ? size : sizeof(inString));
    inString[sizeof(inString) - 1] = '\0';
    lou_compileString(tableList, inString);

    // Test lou_charToDots
    lou_charToDots(tableList, inbuf, outbuf, inlen, 0);

    // Test lou_backTranslate
    int outputPos[256];
    int inputPos[256];
    int cursorPos = 0;
    lou_backTranslate(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, 0);

    return 0;
}