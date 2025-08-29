// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_multi_init at multi.c:272:8 in multi.h
// curl_easy_init at easy.c:351:7 in easy.h
// curl_multi_cleanup at multi.c:2652:11 in multi.h
// curl_multi_wakeup at multi.c:1360:11 in multi.h
// curl_multi_timeout at multi.c:3099:11 in multi.h
// curl_multi_socket_all at multi.c:3047:11 in multi.h
// curl_multi_add_handle at multi.c:294:11 in multi.h
// curl_multi_perform at multi.c:2552:11 in multi.h
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

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    CURL *curl_handle = curl_easy_init();
    if (!curl_handle) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Fuzz curl_multi_wakeup
    curl_multi_wakeup(multi_handle);

    // Fuzz curl_multi_timeout
    long timeout;
    curl_multi_timeout(multi_handle, &timeout);

    // Fuzz curl_multi_socket_all
    int running_handles;
    curl_multi_socket_all(multi_handle, &running_handles);

    // Fuzz curl_multi_add_handle
    curl_multi_add_handle(multi_handle, curl_handle);

    // Fuzz curl_multi_perform
    curl_multi_perform(multi_handle, &running_handles);

    // Cleanup
    curl_multi_remove_handle(multi_handle, curl_handle);
    curl_easy_cleanup(curl_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}