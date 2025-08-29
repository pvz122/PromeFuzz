// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_maprintf at mprintf.c:1150:7 in mprintf.h
// curl_free at escape.c:208:6 in curl.h
// curl_msnprintf at mprintf.c:1095:5 in mprintf.h
// curl_mprintf at mprintf.c:1187:5 in mprintf.h
// curl_getenv at getenv.c:77:7 in curl.h
// curl_free at escape.c:208:6 in curl.h
// curl_maprintf at mprintf.c:1150:7 in mprintf.h
// curl_free at escape.c:208:6 in curl.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <curl/mprintf.h>
#include <curl/curl.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

static void test_mvaprintf(const uint8_t *Data, size_t Size) {
    if (Size == 0) return;
    char *mvaprintf_result = curl_maprintf("%.*s", static_cast<int>(Size), Data);
    if (mvaprintf_result) {
        curl_free(mvaprintf_result);
    }
}

static void test_mvsnprintf(const uint8_t *Data, size_t Size) {
    if (Size == 0) return;
    char buffer[256];
    int mvsnprintf_result = curl_msnprintf(buffer, sizeof(buffer), "%.*s", static_cast<int>(Size), Data);
    if (mvsnprintf_result < 0) {
        // Handle error
    }
}

static void test_mvprintf(const uint8_t *Data, size_t Size) {
    if (Size == 0) return;
    int mvprintf_result = curl_mprintf("%.*s", static_cast<int>(Size), Data);
    if (mvprintf_result < 0) {
        // Handle error
    }
}

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // curl_getenv
    char *env_var = curl_getenv("FUZZ_ENV_VAR");
    if (env_var) {
        curl_free(env_var);
    }

    // curl_maprintf
    char *maprintf_result = curl_maprintf("%.*s", static_cast<int>(Size), Data);
    if (maprintf_result) {
        curl_free(maprintf_result);
    }

    // curl_mvaprintf
    test_mvaprintf(Data, Size);

    // curl_mvsnprintf
    test_mvsnprintf(Data, Size);

    // curl_mvprintf
    test_mvprintf(Data, Size);

    return 0;
}