// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_auto_extension at sqlite3.c:125006:16 in sqlite3.h
// sqlite3_enable_load_extension at sqlite3.c:124957:16 in sqlite3.h
// sqlite3_reset_auto_extension at sqlite3.c:125084:17 in sqlite3.h
// sqlite3_cancel_auto_extension at sqlite3.c:125056:16 in sqlite3.h
// sqlite3_load_extension at sqlite3.c:124926:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
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

static void dummy_entry_point() {}

extern "C" int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) return 0;

    // Fuzz sqlite3_auto_extension
    sqlite3_auto_extension(dummy_entry_point);

    // Fuzz sqlite3_enable_load_extension
    int onoff = Data[0] % 2;
    sqlite3_enable_load_extension(db, onoff);

    // Fuzz sqlite3_reset_auto_extension
    sqlite3_reset_auto_extension();

    // Fuzz sqlite3_cancel_auto_extension
    sqlite3_cancel_auto_extension(dummy_entry_point);

    // Fuzz sqlite3_load_extension
    char *zErrMsg = nullptr;
    const char *zFile = "./dummy_file";
    const char *zProc = nullptr;
    FILE *fp = fopen(zFile, "wb");
    if (fp) {
        fwrite(Data, 1, Size, fp);
        fclose(fp);
        sqlite3_load_extension(db, zFile, zProc, &zErrMsg);
        if (zErrMsg) {
            sqlite3_free(zErrMsg);
        }
        remove(zFile);
    }

    sqlite3_close(db);
    return 0;
}