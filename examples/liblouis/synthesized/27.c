// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_version at compileTranslationTable.c:5382:1 in liblouis.h
// lou_indexTables at metadata.c:895:1 in liblouis.h
// lou_findTable at metadata.c:1002:1 in liblouis.h
// lou_getTableInfo at metadata.c:1073:1 in liblouis.h
// lou_getEmphClasses at compileTranslationTable.c:5039:1 in liblouis.h
// lou_findTables at metadata.c:1041:1 in liblouis.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <liblouis.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare a dummy query string
    char *query = (char *)malloc(Size + 1);
    if (!query) return 0;
    memcpy(query, Data, Size);
    query[Size] = '\0';

    // Call lou_version
    const char *version = lou_version();

    // Call lou_findTable
    const char *tables[] = {"en-us-g2.ctb", NULL};
    lou_indexTables(tables);
    char *table = lou_findTable(query);
    if (table) free(table);

    // Call lou_getTableInfo
    char *info = lou_getTableInfo("en-us-g2.ctb", query);
    if (info) free(info);

    // Call lou_getEmphClasses
    char const **classes = lou_getEmphClasses("en-us-g2.ctb");
    if (classes) {
        for (int i = 0; classes[i]; i++) {
            // Do nothing, just iterate
        }
        free(classes);
    }

    // Call lou_findTables
    char **foundTables = lou_findTables(query);
    if (foundTables) {
        for (int i = 0; foundTables[i]; i++) {
            free(foundTables[i]);
        }
        free(foundTables);
    }

    free(query);
    return 0;
}