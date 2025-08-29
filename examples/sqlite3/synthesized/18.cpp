// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_status at sqlite3.c:10634:16 in sqlite3.h
// sqlite3_memory_used at sqlite3.c:17086:26 in sqlite3.h
// sqlite3_hard_heap_limit64 at sqlite3.c:17026:26 in sqlite3.h
// sqlite3_soft_heap_limit64 at sqlite3.c:16984:26 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    int op = *reinterpret_cast<const int*>(Data);
    int pCurrent, pHighwater;
    int resetFlag = op % 2;

    sqlite3_status(op, &pCurrent, &pHighwater, resetFlag);

    sqlite3_int64 memoryUsed = sqlite3_memory_used();

    sqlite3_int64 hardLimit = 0;
    if (Size >= sizeof(sqlite3_int64)) {
        hardLimit = *reinterpret_cast<const sqlite3_int64*>(Data);
    }
    sqlite3_hard_heap_limit64(hardLimit);

    sqlite3_int64 softLimit = 0;
    if (Size >= sizeof(sqlite3_int64)) {
        softLimit = *reinterpret_cast<const sqlite3_int64*>(Data);
    }
    sqlite3_soft_heap_limit64(softLimit);

    return 0;
}