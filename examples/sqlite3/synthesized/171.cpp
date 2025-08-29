// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_create_function at sqlite3.c:169818:16 in sqlite3.h
// sqlite3_value_int at sqlite3.c:77585:16 in sqlite3.h
// sqlite3_value_blob at sqlite3.c:77563:24 in sqlite3.h
// sqlite3_set_auxdata at sqlite3.c:78563:17 in sqlite3.h
// sqlite3_value_blob at sqlite3.c:77563:24 in sqlite3.h
// sqlite3_value_bytes at sqlite3.c:77576:16 in sqlite3.h
// sqlite3_result_text16be at sqlite3.c:77990:17 in sqlite3.h
// sqlite3_result_text16 at sqlite3.c:77981:17 in sqlite3.h
// sqlite3_result_text16le at sqlite3.c:77999:17 in sqlite3.h
// sqlite3_result_blob at sqlite3.c:77816:17 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_bind_blob at sqlite3.c:79096:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
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

static void dummy_destructor(void*) {}

extern "C" int LLVMFuzzerTestOneInput_171(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3* db;
    sqlite3_open(":memory:", &db);

    sqlite3_stmt* stmt;
    const char* sql = "SELECT 1";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    // Create a valid sqlite3_context by using a custom SQL function
    sqlite3_create_function(db, "test_func", 1, SQLITE_UTF8, nullptr, [](sqlite3_context* context, int argc, sqlite3_value** argv) {
        int N = static_cast<int>(sqlite3_value_int(argv[0]) % 256);
        void* aux_data = const_cast<void*>(reinterpret_cast<const void*>(sqlite3_value_blob(argv[0])));
        sqlite3_set_auxdata(context, N, aux_data, dummy_destructor);

        const void* text_data = reinterpret_cast<const void*>(sqlite3_value_blob(argv[0]));
        int text_size = static_cast<int>(sqlite3_value_bytes(argv[0]));
        sqlite3_result_text16be(context, text_data, text_size, dummy_destructor);
        sqlite3_result_text16(context, text_data, text_size, dummy_destructor);
        sqlite3_result_text16le(context, text_data, text_size, dummy_destructor);
        sqlite3_result_blob(context, text_data, text_size, dummy_destructor);
    }, nullptr, nullptr);

    // Execute the custom function with fuzz data
    char query[256];
    snprintf(query, sizeof(query), "SELECT test_func(?)");
    sqlite3_stmt* func_stmt;
    sqlite3_prepare_v2(db, query, -1, &func_stmt, nullptr);
    sqlite3_bind_blob(func_stmt, 1, Data, Size, SQLITE_STATIC);
    sqlite3_step(func_stmt);
    sqlite3_finalize(func_stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}