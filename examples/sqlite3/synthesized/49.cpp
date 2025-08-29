// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_mprintf at sqlite3.c:19100:18 in sqlite3.h
// sqlite3_mprintf at sqlite3.c:19100:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_blob_open at sqlite3.c:89612:16 in sqlite3.h
// sqlite3_blob_close at sqlite3.c:89848:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <sqlite3.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize sqlite3
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Use the first byte to determine the format string
    const char *format = (Data[0] % 2 == 0) ? "%s" : "%d";

    // Create a null-terminated string from the input data
    char *input = new char[Size];
    memcpy(input, Data + 1, Size - 1);
    input[Size - 1] = '\0';

    // Use the null-terminated string with sqlite3_mprintf
    char *str1 = sqlite3_mprintf(format, input);
    char *str2 = sqlite3_mprintf(format, input);

    // Free the allocated strings
    sqlite3_free(str1);
    sqlite3_free(str2);
    delete[] input;

    // Open a BLOB handle
    sqlite3_blob *pBlob = nullptr;
    sqlite3_blob_open(db, "main", "dummy_table", "dummy_column", 1, 0, &pBlob);

    // Close the BLOB handle if it was opened
    if (pBlob) {
        sqlite3_blob_close(pBlob);
    }

    // Clean up
    sqlite3_close(db);

    return 0;
}