// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_value_dup at sqlite3.c:77726:27 in sqlite3.h
// sqlite3_value_text16be at sqlite3.c:77615:24 in sqlite3.h
// sqlite3_value_subtype at sqlite3.c:77591:25 in sqlite3.h
// sqlite3_value_text16 at sqlite3.c:77612:24 in sqlite3.h
// sqlite3_value_free at sqlite3.c:77752:17 in sqlite3.h
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <sqlite3.h>

extern "C" int LLVMFuzzerTestOneInput_138(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    sqlite3_value *value = sqlite3_value_dup(nullptr);
    if (value) {
        sqlite3_value_text16be(value);
        sqlite3_value_subtype(value);
        sqlite3_value_text16(value);
        sqlite3_value_free(value);
    }

    return 0;
}