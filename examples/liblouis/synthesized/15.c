// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_getDataPath at compileTranslationTable.c:70:1 in liblouis.h
// lou_listTables at metadata.c:1098:1 in liblouis.h
// lou_setDataPath at compileTranslationTable.c:59:1 in liblouis.h
// lou_indexTables at metadata.c:895:1 in liblouis.h
// lou_findTable at metadata.c:1002:1 in liblouis.h
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

static void cleanup_char_array(char **array) {
    if (array) {
        for (int i = 0; array[i]; i++) {
            free(array[i]);
        }
        free(array);
    }
}

int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz lou_getDataPath
    char *dataPath = lou_getDataPath();
    if (dataPath) {
        // Do not free dataPath as it is not malloc()-ed
    }

    // Fuzz lou_listTables
    char **tables = lou_listTables();
    cleanup_char_array(tables);

    // Fuzz lou_setDataPath
    char *path = malloc(Size + 1);
    if (!path) return 0;
    memcpy(path, Data, Size);
    path[Size] = '\0';
    char *setPath = lou_setDataPath(path);
    if (setPath) {
        // Do not free setPath as it is not malloc()-ed
    }
    free(path);

    // Fuzz lou_indexTables
    const char *tablePaths[] = {"./dummy_file", NULL};
    lou_indexTables(tablePaths);

    // Fuzz lou_findTable
    char *query = malloc(Size + 1);
    if (!query) return 0;
    memcpy(query, Data, Size);
    query[Size] = '\0';
    char *foundTable = lou_findTable(query);
    if (foundTable) {
        free(foundTable);
    }
    free(query);

    return 0;
}