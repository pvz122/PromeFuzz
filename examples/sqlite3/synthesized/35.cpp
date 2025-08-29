// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_db_name at sqlite3.c:172610:24 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_file_control at sqlite3.c:171810:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_file_control at sqlite3.c:171810:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
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
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    int rc;

    // Open the database
    rc = sqlite3_open("./dummy_file", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Get the database name
    const char *db_name = sqlite3_db_name(db, 0);
    if (db_name == nullptr) {
        sqlite3_close(db);
        return 0;
    }

    // Perform file control operations
    int lock_state;
    rc = sqlite3_file_control(db, db_name, SQLITE_FCNTL_LOCKSTATE, &lock_state);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    int chunk_size;
    rc = sqlite3_file_control(db, db_name, SQLITE_FCNTL_CHUNK_SIZE, &chunk_size);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Close the database
    rc = sqlite3_close(db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Reopen the database
    rc = sqlite3_open("./dummy_file", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Close the database again
    sqlite3_close(db);

    return 0;
}