// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
// lou_translateString at lou_translateString.c:1117:1 in liblouis.h
// lou_translate at lou_translateString.c:1124:1 in liblouis.h
// lou_charToDots at lou_translateString.c:4154:1 in liblouis.h
// lou_backTranslate at lou_backTranslateString.c:150:1 in liblouis.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <liblouis.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    write_dummy_file(data, size);

    const char *tableList = "./dummy_file";
    const void *table = lou_getTable(tableList);
    if (!table) return 0;

    widechar inbuf[256];
    widechar outbuf[256];
    int inlen = sizeof(inbuf) / sizeof(widechar);
    int outlen = sizeof(outbuf) / sizeof(widechar);
    formtype typeform[256];
    char spacing[256];
    int outputPos[256];
    int inputPos[256];
    int cursorPos = 0;
    int mode = 0;

    for (int i = 0; i < inlen; i++) {
        inbuf[i] = data[i % size];
        typeform[i] = data[i % size];
        spacing[i] = data[i % size];
    }

    lou_translateString(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, mode);
    lou_translate(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, mode);
    lou_charToDots(tableList, inbuf, outbuf, inlen, mode);
    lou_backTranslate(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, mode);

    return 0;
}