// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_overload_function at sqlite3.c:169924:16 in sqlite3.h
// sqlite3_create_module at sqlite3.c:142774:16 in sqlite3.h
// sqlite3_drop_modules at sqlite3.c:142806:16 in sqlite3.h
// sqlite3_declare_vtab at sqlite3.c:143477:16 in sqlite3.h
// sqlite3_create_module_v2 at sqlite3.c:142789:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_160(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Ensure funcName is null-terminated
    char *funcName = new char[Size + 1];
    memcpy(funcName, Data, Size);
    funcName[Size] = '\0';

    int nArg = static_cast<int>(Size % 10);
    sqlite3_overload_function(db, funcName, nArg);

    delete[] funcName;

    // Fuzz sqlite3_create_module
    const char *moduleName = "fuzz_module";
    sqlite3_module module = {0};
    void *pClientData = nullptr;
    sqlite3_create_module(db, moduleName, &module, pClientData);

    // Fuzz sqlite3_drop_modules
    const char *azKeep[] = {nullptr};
    sqlite3_drop_modules(db, azKeep);

    // Fuzz sqlite3_declare_vtab
    const char *zSQL = "CREATE TABLE fuzz_table (id INTEGER PRIMARY KEY, name TEXT)";
    sqlite3_declare_vtab(db, zSQL);

    // Fuzz sqlite3_create_module_v2
    void (*xDestroy)(void *) = nullptr;
    sqlite3_create_module_v2(db, moduleName, &module, pClientData, xDestroy);

    sqlite3_close(db);
    return 0;
}