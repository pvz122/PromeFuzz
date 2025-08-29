// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
// lou_getTable at compileTranslationTable.c:5082:1 in liblouis.h
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

int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char *tableList = (char *)malloc(Size + 1);
    if (!tableList) return 0;

    memcpy(tableList, Data, Size);
    tableList[Size] = '\0';

    const void *table = NULL;

    table = lou_getTable(tableList);
    table = lou_getTable(tableList);
    table = lou_getTable(tableList);
    table = lou_getTable(tableList);
    table = lou_getTable(tableList);
    table = lou_getTable(tableList);
    table = lou_getTable(tableList);
    table = lou_getTable(tableList);
    table = lou_getTable(tableList);
    table = lou_getTable(tableList);
    table = lou_getTable(tableList);
    table = lou_getTable(tableList);
    table = lou_getTable(tableList);
    table = lou_getTable(tableList);
    table = lou_getTable(tableList);
    table = lou_getTable(tableList);

    lou_free();

    free(tableList);
    return 0;
}