// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_init at easy.c:351:7 in easy.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_easy_escape at escape.c:58:7 in curl.h
// curl_free at escape.c:208:6 in curl.h
// curl_escape at escape.c:44:7 in curl.h
// curl_free at escape.c:208:6 in curl.h
// curl_unescape at escape.c:50:7 in curl.h
// curl_free at escape.c:208:6 in curl.h
// curl_easy_unescape at escape.c:181:7 in curl.h
// curl_free at escape.c:208:6 in curl.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <curl/curl.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    CURL *handle = curl_easy_init();
    if (!handle) return 0;

    // Create a null-terminated string from the input data
    char *input = (char *)malloc(Size + 1);
    if (!input) {
        curl_easy_cleanup(handle);
        return 0;
    }
    memcpy(input, Data, Size);
    input[Size] = '\0';

    // Test curl_easy_escape
    char *escaped = curl_easy_escape(handle, input, Size);
    if (escaped) {
        curl_free(escaped);
    }

    // Test curl_escape
    char *escaped_old = curl_escape(input, Size);
    if (escaped_old) {
        curl_free(escaped_old);
    }

    // Test curl_unescape
    char *unescaped_old = curl_unescape(input, Size);
    if (unescaped_old) {
        curl_free(unescaped_old);
    }

    // Test curl_easy_unescape
    int outlength = 0;
    char *unescaped = curl_easy_unescape(handle, input, Size, &outlength);
    if (unescaped) {
        curl_free(unescaped);
    }

    free(input);
    curl_easy_cleanup(handle);
    return 0;
}