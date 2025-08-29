// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_indexTables at metadata.c:895:1 in liblouis.h
// lou_findTable at metadata.c:1002:1 in liblouis.h
// lou_registerTableResolver at compileTranslationTable.c:4833:1 in liblouis.h
// lou_getTableInfo at metadata.c:1073:1 in liblouis.h
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

static char **tables = NULL;
static char *query = NULL;
static char *key = NULL;

static void cleanup() {
    if (tables) {
        for (int i = 0; tables[i]; i++) {
            free(tables[i]);
        }
        free(tables);
    }
    if (query) free(query);
    if (key) free(key);
}

static char **custom_resolver(const char *table, const char *base) {
    char **result = malloc(2 * sizeof(char *));
    if (!result) return NULL;
    result[0] = strdup(table);
    result[1] = NULL;
    return result;
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize tables
    tables = malloc(2 * sizeof(char *));
    if (!tables) return 0;
    tables[0] = strdup("en-us-g2.ctb");
    tables[1] = NULL;

    // Initialize query and key
    query = malloc(Size + 1);
    if (!query) {
        cleanup();
        return 0;
    }
    memcpy(query, Data, Size);
    query[Size] = '\0';

    key = malloc(Size + 1);
    if (!key) {
        cleanup();
        return 0;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0';

    // Call API functions
    lou_indexTables(tables);
    lou_findTable(query);
    lou_registerTableResolver(custom_resolver);
    lou_getTableInfo(tables[0], key);
    lou_findTables(query);

    // Cleanup
    cleanup();
    return 0;
}