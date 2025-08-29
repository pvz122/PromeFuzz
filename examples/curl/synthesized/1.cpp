// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_init at easy.c:351:7 in easy.h
// curl_easy_setopt at setopt.c:3057:10 in easy.h
// curl_easy_perform at easy.c:827:10 in easy.h
// curl_strnequal at strequal.c:80:5 in curl.h
// curl_easy_pause at easy.c:1129:10 in curl.h
// curl_easy_recv at easy.c:1241:10 in easy.h
// curl_strequal at strequal.c:69:5 in curl.h
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize CURL
    CURL *curl = curl_easy_init();
    if (!curl) return 0;

    // Fuzz curl_easy_perform
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    curl_easy_perform(curl);

    // Fuzz curl_strnequal
    const char *s1 = reinterpret_cast<const char*>(Data);
    const char *s2 = "fuzz_string";
    size_t n = Size < 10 ? Size : 10;
    curl_strnequal(s1, s2, n);

    // Fuzz curl_easy_pause
    curl_easy_pause(curl, CURLPAUSE_RECV);

    // Fuzz curl_easy_recv
    char buffer[1024];
    size_t nread;
    curl_easy_recv(curl, buffer, sizeof(buffer), &nread);

    // Fuzz curl_strequal
    curl_strequal(s1, s2);

    // Cleanup
    curl_easy_cleanup(curl);

    return 0;
}