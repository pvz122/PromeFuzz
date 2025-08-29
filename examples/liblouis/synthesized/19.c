// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_indexTables at metadata.c:895:1 in liblouis.h
// lou_findTable at metadata.c:1002:1 in liblouis.h
// lou_getTableInfo at metadata.c:1073:1 in liblouis.h
// lou_findTables at metadata.c:1041:1 in liblouis.h
// lou_getEmphClasses at compileTranslationTable.c:5039:1 in liblouis.h
// lou_free at compileTranslationTable.c:5327:1 in liblouis.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <liblouis.h>

static const char *tables[] = {
    "en-us-g2.ctb",
    "en-ueb-g1.ctb",
    "fr-bfu-g2.ctb",
    NULL
};

int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char *query = (char *)malloc(Size + 1);
    if (!query) return 0;
    memcpy(query, Data, Size);
    query[Size] = '\0';

    lou_indexTables(tables);

    char *table = lou_findTable(query);
    if (table) {
        char *info = lou_getTableInfo(table, "language");
        if (info) {
            free(info);
        }
        // Do not free(table) here as it is managed by liblouis
    }

    char **tablesFound = lou_findTables(query);
    if (tablesFound) {
        for (int i = 0; tablesFound[i]; i++) {
            free(tablesFound[i]);
        }
        free(tablesFound);
    }

    char const **emphClasses = lou_getEmphClasses("en-us-g2.ctb");
    if (emphClasses) {
        for (int i = 0; emphClasses[i]; i++) {
            // Do nothing, just iterate
        }
        free(emphClasses);
    }

    free(query);

    // Clean up allocated memory by lou_indexTables
    lou_free();

    return 0;
}