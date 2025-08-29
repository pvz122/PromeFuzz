// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_init at easy.c:351:7 in easy.h
// curl_easy_setopt at setopt.c:3057:10 in easy.h
// curl_easy_setopt at setopt.c:3057:10 in easy.h
// curl_easy_perform at easy.c:827:10 in easy.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_ws_send at ws.c:1160:22 in websockets.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_easy_send at easy.c:1324:10 in easy.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_ws_recv at ws.c:938:22 in websockets.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_easy_recv at easy.c:1241:10 in easy.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
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
#include <curl/websockets.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    CURL *curl = curl_easy_init();
    if (!curl) return 0;

    curl_easy_setopt(curl, CURLOPT_URL, "ws://example.com");
    curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        return 0;
    }

    size_t sent = 0;
    char *buffer = (char *)malloc(Size);
    if (!buffer) {
        curl_easy_cleanup(curl);
        return 0;
    }
    memcpy(buffer, Data, Size);

    // Test curl_ws_send
    res = curl_ws_send(curl, buffer, Size, &sent, 0, CURLWS_BINARY);
    if (res != CURLE_OK && res != CURLE_AGAIN) {
        free(buffer);
        curl_easy_cleanup(curl);
        return 0;
    }

    // Test curl_easy_send
    res = curl_easy_send(curl, buffer, Size, &sent);
    if (res != CURLE_OK && res != CURLE_AGAIN) {
        free(buffer);
        curl_easy_cleanup(curl);
        return 0;
    }

    // Test curl_ws_recv
    size_t recv = 0;
    const struct curl_ws_frame *meta = nullptr;
    res = curl_ws_recv(curl, buffer, Size, &recv, &meta);
    if (res != CURLE_OK && res != CURLE_AGAIN) {
        free(buffer);
        curl_easy_cleanup(curl);
        return 0;
    }

    // Test curl_easy_recv
    res = curl_easy_recv(curl, buffer, Size, &recv);
    if (res != CURLE_OK && res != CURLE_AGAIN) {
        free(buffer);
        curl_easy_cleanup(curl);
        return 0;
    }

    free(buffer);
    curl_easy_cleanup(curl);
    return 0;
}