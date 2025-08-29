// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_mutex_alloc at sqlite3.c:15684:27 in sqlite3.h
// sqlite3_mutex_enter at sqlite3.c:15716:17 in sqlite3.h
// sqlite3_mutex_try at sqlite3.c:15727:16 in sqlite3.h
// sqlite3_mutex_leave at sqlite3.c:15742:17 in sqlite3.h
// sqlite3_mutex_leave at sqlite3.c:15742:17 in sqlite3.h
// sqlite3_mutex_free at sqlite3.c:15705:17 in sqlite3.h
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
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    int mutex_type = Data[0] % 15;
    sqlite3_mutex *mutex = sqlite3_mutex_alloc(mutex_type);
    if (mutex) {
        sqlite3_mutex_enter(mutex);
        if (mutex_type == SQLITE_MUTEX_RECURSIVE) {
            if (sqlite3_mutex_try(mutex) == SQLITE_OK) {
                sqlite3_mutex_leave(mutex); // Ensure reference count is balanced
            }
        }
        sqlite3_mutex_leave(mutex);
        sqlite3_mutex_free(mutex);
    }

    return 0;
}