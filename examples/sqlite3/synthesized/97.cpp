// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_backup_init at sqlite3.c:69129:28 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_backup_step at sqlite3.c:69303:16 in sqlite3.h
// sqlite3_backup_pagecount at sqlite3.c:69628:16 in sqlite3.h
// sqlite3_backup_remaining at sqlite3.c:69614:16 in sqlite3.h
// sqlite3_backup_finish at sqlite3.c:69560:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db1, *db2;
    if (sqlite3_open(":memory:", &db1) != SQLITE_OK) return 0;
    if (sqlite3_open(":memory:", &db2) != SQLITE_OK) {
        sqlite3_close(db1);
        return 0;
    }

    sqlite3_backup *backup = sqlite3_backup_init(db2, "main", db1, "main");
    if (!backup) {
        sqlite3_close(db1);
        sqlite3_close(db2);
        return 0;
    }

    int nPage = Data[0] % 100;
    sqlite3_backup_step(backup, nPage);

    sqlite3_backup_pagecount(backup);
    sqlite3_backup_remaining(backup);

    sqlite3_backup_finish(backup);
    sqlite3_close(db1);
    sqlite3_close(db2);

    return 0;
}