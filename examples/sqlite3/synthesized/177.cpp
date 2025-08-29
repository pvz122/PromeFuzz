// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_bind_double at sqlite3.c:79118:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_column_value at sqlite3.c:78784:27 in sqlite3.h
// sqlite3_value_dup at sqlite3.c:77726:27 in sqlite3.h
// sqlite3_value_double at sqlite3.c:77582:19 in sqlite3.h
// sqlite3_value_pointer at sqlite3.c:77595:18 in sqlite3.h
// sqlite3_value_text16le at sqlite3.c:77618:24 in sqlite3.h
// sqlite3_value_free at sqlite3.c:77752:17 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
#include <sqlite3.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_177(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return 0;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) return 0;

    sqlite3_stmt *stmt;
    const char *sql = "SELECT ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_double(stmt, 1, *reinterpret_cast<const double*>(Data));

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        sqlite3_value *value = sqlite3_column_value(stmt, 0);

        // Ensure the value is protected before using it
        sqlite3_value *protected_value = sqlite3_value_dup(value);
        if (protected_value) {
            double d = sqlite3_value_double(protected_value);

            const char *subtype = "test_subtype";
            void *ptr = sqlite3_value_pointer(protected_value, subtype);

            const void *text16le = sqlite3_value_text16le(protected_value);

            sqlite3_value_free(protected_value);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}