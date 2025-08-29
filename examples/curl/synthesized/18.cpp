// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_multi_init at multi.c:272:8 in multi.h
// curl_easy_init at easy.c:351:7 in easy.h
// curl_multi_cleanup at multi.c:2652:11 in multi.h
// curl_multi_setopt at multi.c:2951:11 in multi.h
// curl_multi_setopt at multi.c:2951:11 in multi.h
// curl_multi_add_handle at multi.c:294:11 in multi.h
// curl_multi_perform at multi.c:2552:11 in multi.h
// curl_multi_assign at multi.c:3378:11 in multi.h
// curl_multi_socket_action at multi.c:3038:11 in multi.h
// curl_multi_strerror at strerror.c:364:1 in multi.h
// curl_multi_remove_handle at multi.c:589:11 in multi.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_multi_cleanup at multi.c:2652:11 in multi.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <curl/multi.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

static int dummy_socket_callback(CURL *easy, curl_socket_t s, int what, void *userp, void *socketp) {
    return 0;
}

static int dummy_timer_callback(CURLM *multi, long timeout_ms, void *userp) {
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) return 0;

    CURL *easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    curl_multi_setopt(multi_handle, CURLMOPT_SOCKETFUNCTION, dummy_socket_callback);
    curl_multi_setopt(multi_handle, CURLMOPT_TIMERFUNCTION, dummy_timer_callback);

    curl_multi_add_handle(multi_handle, easy_handle);

    int running_handles = 0;
    curl_multi_perform(multi_handle, &running_handles);

    curl_socket_t sockfd = static_cast<curl_socket_t>(Data[0]);
    void *sockp = nullptr;
    curl_multi_assign(multi_handle, sockfd, sockp);

    curl_multi_socket_action(multi_handle, sockfd, Data[0] & 0x0F, &running_handles);

    CURLMcode code = static_cast<CURLMcode>(Data[0] % CURLM_LAST);
    const char *error_str = curl_multi_strerror(code);

    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}