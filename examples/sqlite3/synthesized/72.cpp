// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_wal_autocheckpoint at sqlite3.c:170197:16 in sqlite3.h
// sqlite3_busy_timeout at sqlite3.c:169546:16 in sqlite3.h
// sqlite3_setlk_timeout at sqlite3.c:169566:16 in sqlite3.h
// sqlite3_wal_checkpoint at sqlite3.c:170309:16 in sqlite3.h
// sqlite3_wal_checkpoint_v2 at sqlite3.c:170245:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    int n = static_cast<int>(Data[0]);
    sqlite3_wal_autocheckpoint(db, n);

    int timeout = static_cast<int>(Data[0]);
    sqlite3_busy_timeout(db, timeout);

    int setlk_timeout = static_cast<int>(Data[0]);
    sqlite3_setlk_timeout(db, setlk_timeout, 0);

    sqlite3_wal_checkpoint(db, "main");

    int log_frames, ckpt_frames;
    sqlite3_wal_checkpoint_v2(db, "main", SQLITE_CHECKPOINT_PASSIVE, &log_frames, &ckpt_frames);

    sqlite3_close(db);
    return 0;
}