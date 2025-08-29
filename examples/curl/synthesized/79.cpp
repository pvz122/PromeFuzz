// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_setopt at setopt.c:3057:10 in easy.h
// curl_easy_setopt at setopt.c:3057:10 in easy.h
// curl_easy_perform at easy.c:827:10 in easy.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_ws_send at ws.c:1160:22 in websockets.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_easy_recv at easy.c:1241:10 in easy.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_ws_meta at ws.c:1329:41 in websockets.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_easy_init at easy.c:351:7 in easy.h
#include <curl/curl.h>
#include <curl/websockets.h>
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size) {
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

    size_t sent;
    res = curl_ws_send(curl, Data, Size, &sent, 0, CURLWS_BINARY);
    if (res != CURLE_OK && res != CURLE_AGAIN) {
        curl_easy_cleanup(curl);
        return 0;
    }

    size_t n;
    uint8_t recv_buffer[1024];
    res = curl_easy_recv(curl, recv_buffer, sizeof(recv_buffer), &n);
    if (res != CURLE_OK && res != CURLE_AGAIN) {
        curl_easy_cleanup(curl);
        return 0;
    }

    const struct curl_ws_frame *meta = curl_ws_meta(curl);
    if (meta) {
        // Metadata available, but we don't use it in this fuzz driver
    }

    curl_easy_cleanup(curl);
    return 0;
}