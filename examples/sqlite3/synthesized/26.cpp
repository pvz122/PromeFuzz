// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_stricmp at sqlite3.c:22070:16 in sqlite3.h
// sqlite3_stricmp at sqlite3.c:22070:16 in sqlite3.h
// sqlite3_stricmp at sqlite3.c:22070:16 in sqlite3.h
// sqlite3_strnicmp at sqlite3.c:22097:16 in sqlite3.h
// sqlite3_stricmp at sqlite3.c:22070:16 in sqlite3.h
// sqlite3_stricmp at sqlite3.c:22070:16 in sqlite3.h
// sqlite3_stricmp at sqlite3.c:22070:16 in sqlite3.h
// sqlite3_strglob at sqlite3.c:117109:16 in sqlite3.h
// sqlite3_strglob at sqlite3.c:117109:16 in sqlite3.h
// sqlite3_stricmp at sqlite3.c:22070:16 in sqlite3.h
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Ensure the strings are null-terminated
    std::vector<char> str1(Data, Data + Size / 2);
    str1.push_back('\0');
    std::vector<char> str2(Data + Size / 2, Data + Size);
    str2.push_back('\0');

    sqlite3_stricmp(str1.data(), str2.data());
    sqlite3_stricmp(str2.data(), str1.data());
    sqlite3_stricmp(str1.data(), str1.data());

    sqlite3_strnicmp(str1.data(), str2.data(), Size / 2);

    sqlite3_stricmp(str2.data(), str1.data());
    sqlite3_stricmp(str1.data(), str2.data());
    sqlite3_stricmp(str2.data(), str2.data());

    sqlite3_strglob(str1.data(), str2.data());
    sqlite3_strglob(str2.data(), str1.data());

    sqlite3_stricmp(str1.data(), str2.data());

    return 0;
}