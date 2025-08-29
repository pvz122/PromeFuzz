// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_set_authorizer at sqlite3.c:108676:16 in sqlite3.h
// sqlite3_create_module at sqlite3.c:142774:16 in sqlite3.h
// sqlite3_create_function at sqlite3.c:169818:16 in sqlite3.h
// sqlite3_set_clientdata at sqlite3.c:171534:16 in sqlite3.h
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

static int authCallback(void* pUserData, int actionCode, const char* arg1, const char* arg2, const char* arg3, const char* arg4) {
    return SQLITE_OK;
}

static void funcCallback(sqlite3_context* context, int argc, sqlite3_value** argv) {}

static void stepCallback(sqlite3_context* context, int argc, sqlite3_value** argv) {}

static void finalCallback(sqlite3_context* context) {}

static void clientDataDestructor(void* data) {}

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t* Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3* db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) return 0;

    sqlite3_set_authorizer(db, authCallback, nullptr);

    sqlite3_module module = {0};
    sqlite3_create_module(db, "test_module", &module, nullptr);

    sqlite3_create_function(db, "test_func", -1, SQLITE_UTF8, nullptr, funcCallback, stepCallback, finalCallback);

    sqlite3_set_clientdata(db, "test_data", nullptr, clientDataDestructor);

    sqlite3_create_module_v2(db, "test_module_v2", &module, nullptr, clientDataDestructor);

    sqlite3_close(db);
    return 0;
}