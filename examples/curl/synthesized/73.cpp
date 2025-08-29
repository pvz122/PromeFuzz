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

extern "C" int LLVMFuzzerTestOneInput_73(const uint8_t *Data, size_t Size) {
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
    size_t recv = 0;
    curl_off_t fragsize = Size;
    unsigned int flags = CURLWS_BINARY;
    const struct curl_ws_frame *meta = nullptr;

    // Fuzz curl_ws_send
    curl_ws_send(curl, Data, Size, &sent, fragsize, flags);

    // Fuzz curl_easy_send
    curl_easy_send(curl, Data, Size, &sent);

    // Fuzz curl_ws_recv
    char *recv_buffer = (char *)malloc(Size);
    if (recv_buffer) {
        curl_ws_recv(curl, recv_buffer, Size, &recv, &meta);
        free(recv_buffer);
    }

    // Fuzz curl_ws_meta
    curl_ws_meta(curl);

    // Fuzz curl_easy_recv
    char *recv_buffer2 = (char *)malloc(Size);
    if (recv_buffer2) {
        curl_easy_recv(curl, recv_buffer2, Size, &recv);
        free(recv_buffer2);
    }

    curl_easy_cleanup(curl);
    return 0;
}