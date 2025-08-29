// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_config at sqlite3.c:168141:16 in sqlite3.h
// sqlite3_config at sqlite3.c:168141:16 in sqlite3.h
// sqlite3_config at sqlite3.c:168141:16 in sqlite3.h
// sqlite3_threadsafe at sqlite3.c:167832:16 in sqlite3.h
// sqlite3_initialize at sqlite3.c:167905:16 in sqlite3.h
// sqlite3_enable_shared_cache at sqlite3.c:57572:16 in sqlite3.h
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize SQLite
    sqlite3_config(SQLITE_CONFIG_SINGLETHREAD);
    sqlite3_config(SQLITE_CONFIG_MULTITHREAD);
    sqlite3_config(SQLITE_CONFIG_SERIALIZED);

    int threadsafe = sqlite3_threadsafe();
    if (threadsafe == 0) return 0;

    sqlite3_initialize();

    // Enable shared cache
    sqlite3_enable_shared_cache(Data[0] % 2);

    // Open a database
    sqlite3 *db;
    const char *filename = "./dummy_file";
    FILE *fp = fopen(filename, "wb");
    if (!fp) return 0;
    fwrite(Data, 1, Size, fp);
    fclose(fp);

    int rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Close the database
    sqlite3_close(db);

    // Remove the dummy file
    remove(filename);

    return 0;
}