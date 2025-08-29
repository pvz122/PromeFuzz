// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_malloc at sqlite3.c:17226:18 in sqlite3.h
// sqlite3_vtab_in_next at sqlite3.c:78458:16 in sqlite3.h
// sqlite3_value_numeric_type at sqlite3.c:80698:16 in sqlite3.h
// sqlite3_vtab_rhs_value at sqlite3.c:154034:16 in sqlite3.h
// sqlite3_vtab_in_first at sqlite3.c:78450:16 in sqlite3.h
// sqlite3_value_type at sqlite3.c:77626:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
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
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_115(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    sqlite3_value *value = (sqlite3_value *)sqlite3_malloc(64); // Allocate a dummy buffer
    if (!value) {
        return 0;
    }

    sqlite3_value *pOut = nullptr;

    // Fuzz sqlite3_vtab_in_next
    sqlite3_vtab_in_next(value, &pOut);

    // Fuzz sqlite3_value_numeric_type
    sqlite3_value_numeric_type(value);

    // Fuzz sqlite3_vtab_rhs_value
    sqlite3_index_info info;
    sqlite3_value *ppVal = nullptr;
    sqlite3_vtab_rhs_value(&info, 0, &ppVal);

    // Fuzz sqlite3_vtab_in_first
    sqlite3_vtab_in_first(value, &pOut);

    // Fuzz sqlite3_value_type
    sqlite3_value_type(value);

    sqlite3_free(value);

    return 0;
}