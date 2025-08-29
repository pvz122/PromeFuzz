// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_init at easy.c:351:7 in easy.h
// curl_easy_setopt at setopt.c:3057:10 in easy.h
// curl_easy_setopt at setopt.c:3057:10 in easy.h
// curl_easy_perform at easy.c:827:10 in easy.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_ws_send at ws.c:1160:22 in websockets.h
// curl_easy_send at easy.c:1324:10 in easy.h
// curl_ws_recv at ws.c:938:22 in websockets.h
// curl_ws_meta at ws.c:1329:41 in websockets.h
// curl_easy_recv at easy.c:1241:10 in easy.h
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
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "ws://example.com");
    curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        return 0;
    }

    // Fuzz curl_ws_send
    size_t sent;
    curl_ws_send(curl, Data, Size, &sent, 0, CURLWS_BINARY);

    // Fuzz curl_easy_send
    size_t n;
    curl_easy_send(curl, Data, Size, &n);

    // Fuzz curl_ws_recv
    uint8_t *recv_buffer = (uint8_t *)malloc(Size);
    size_t recv;
    const struct curl_ws_frame *meta;
    curl_ws_recv(curl, recv_buffer, Size, &recv, &meta);
    free(recv_buffer);

    // Fuzz curl_ws_meta
    curl_ws_meta(curl);

    // Fuzz curl_easy_recv
    uint8_t *easy_recv_buffer = (uint8_t *)malloc(Size);
    size_t easy_recv;
    curl_easy_recv(curl, easy_recv_buffer, Size, &easy_recv);
    free(easy_recv_buffer);

    curl_easy_cleanup(curl);
    return 0;
}