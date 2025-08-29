// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_getTypeformForEmphClass at compileTranslationTable.c:5208:1 in liblouis.h
// lou_getTypeformForEmphClass at compileTranslationTable.c:5208:1 in liblouis.h
// lou_getTypeformForEmphClass at compileTranslationTable.c:5208:1 in liblouis.h
// lou_getTypeformForEmphClass at compileTranslationTable.c:5208:1 in liblouis.h
// lou_getTypeformForEmphClass at compileTranslationTable.c:5208:1 in liblouis.h
// lou_free at compileTranslationTable.c:5327:1 in liblouis.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <liblouis.h>

int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Split the input into two parts: tableList and emphClass
    size_t split = Size / 2;
    char *tableList = (char *)malloc(split + 1);
    char *emphClass = (char *)malloc(Size - split + 1);

    if (!tableList || !emphClass) {
        free(tableList);
        free(emphClass);
        return 0;
    }

    memcpy(tableList, Data, split);
    tableList[split] = '\0';

    memcpy(emphClass, Data + split, Size - split);
    emphClass[Size - split] = '\0';

    // Call the target API functions
    lou_getTypeformForEmphClass(tableList, emphClass);
    lou_getTypeformForEmphClass(tableList, emphClass);
    lou_getTypeformForEmphClass(tableList, emphClass);
    lou_getTypeformForEmphClass(tableList, emphClass);
    lou_getTypeformForEmphClass(tableList, emphClass);

    // Cleanup
    lou_free();
    free(tableList);
    free(emphClass);

    return 0;
}