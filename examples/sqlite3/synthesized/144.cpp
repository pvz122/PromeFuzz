// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_create_collation at sqlite3.c:171408:16 in sqlite3.h
// sqlite3_create_collation16 at sqlite3.c:171446:16 in sqlite3.h
// sqlite3_create_collation_v2 at sqlite3.c:171421:16 in sqlite3.h
// sqlite3_collation_needed at sqlite3.c:171476:16 in sqlite3.h
// sqlite3_collation_needed16 at sqlite3.c:171497:16 in sqlite3.h
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

static int dummyCompare(void*, int, const void*, int, const void*) {
    return 0;
}

static void dummyDestroy(void*) {}

static void dummyCollNeeded(void*, sqlite3*, int, const char*) {}

static void dummyCollNeeded16(void*, sqlite3*, int, const void*) {}

extern "C" int LLVMFuzzerTestOneInput_144(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    int eTextRep = Data[0] % 5;
    const char *zName = reinterpret_cast<const char*>(Data);
    const void *zName16 = reinterpret_cast<const void*>(Data);

    // Ensure zName is null-terminated
    std::vector<char> zNameSafe(Size + 1);
    std::memcpy(zNameSafe.data(), Data, Size);
    zNameSafe[Size] = '\0';
    zName = zNameSafe.data();

    // Ensure zName16 is null-terminated
    std::vector<uint16_t> zName16Safe(Size / 2 + 1);
    std::memcpy(zName16Safe.data(), Data, Size);
    zName16Safe[Size / 2] = 0;
    zName16 = zName16Safe.data();

    sqlite3_create_collation(db, zName, eTextRep, nullptr, dummyCompare);
    sqlite3_create_collation16(db, zName16, eTextRep, nullptr, dummyCompare);
    sqlite3_create_collation_v2(db, zName, eTextRep, nullptr, dummyCompare, dummyDestroy);

    sqlite3_collation_needed(db, nullptr, dummyCollNeeded);
    sqlite3_collation_needed16(db, nullptr, dummyCollNeeded16);

    sqlite3_close(db);
    return 0;
}