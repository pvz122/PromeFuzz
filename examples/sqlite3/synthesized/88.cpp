// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_memory_alarm at sqlite3.c:16961:16 in sqlite3.h
// sqlite3_soft_heap_limit64 at sqlite3.c:16984:26 in sqlite3.h
// sqlite3_memory_used at sqlite3.c:17086:26 in sqlite3.h
// sqlite3_malloc at sqlite3.c:17226:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_memory_highwater at sqlite3.c:17097:26 in sqlite3.h
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

static void memory_alarm_callback(void* pArg, sqlite3_int64 used, int threshold) {
    // Dummy callback function for sqlite3_memory_alarm
}

extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(sqlite3_int64)) return 0;

    sqlite3_int64 threshold = *reinterpret_cast<const sqlite3_int64*>(Data);
    sqlite3_memory_alarm(memory_alarm_callback, nullptr, threshold);

    sqlite3_int64 soft_limit = *reinterpret_cast<const sqlite3_int64*>(Data);
    sqlite3_soft_heap_limit64(soft_limit);

    sqlite3_memory_used();

    int malloc_size = static_cast<int>(Size);
    void* mem = sqlite3_malloc(malloc_size);
    if (mem) {
        sqlite3_free(mem);
    }

    int resetFlag = *reinterpret_cast<const int*>(Data);
    sqlite3_memory_highwater(resetFlag);

    return 0;
}