// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_multi_init at multi.c:272:8 in multi.h
// curl_easy_init at easy.c:351:7 in easy.h
// curl_multi_cleanup at multi.c:2652:11 in multi.h
// curl_multi_add_handle at multi.c:294:11 in multi.h
// curl_multi_perform at multi.c:2552:11 in multi.h
// curl_multi_fdset at multi.c:990:11 in multi.h
// curl_multi_socket_action at multi.c:3038:11 in multi.h
// curl_multi_socket_all at multi.c:3047:11 in multi.h
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

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) return 0;

    CURL *curl_handle = curl_easy_init();
    if (!curl_handle) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    curl_multi_add_handle(multi_handle, curl_handle);

    int running_handles = 0;
    curl_multi_perform(multi_handle, &running_handles);

    fd_set read_fd_set, write_fd_set, exc_fd_set;
    int max_fd = 0;
    FD_ZERO(&read_fd_set);
    FD_ZERO(&write_fd_set);
    FD_ZERO(&exc_fd_set);
    curl_multi_fdset(multi_handle, &read_fd_set, &write_fd_set, &exc_fd_set, &max_fd);

    curl_socket_t s = (curl_socket_t)(Data[0] % 1024); // Simulate a socket
    int ev_bitmask = (int)(Data[0] % 4); // Simulate event bitmask
    curl_multi_socket_action(multi_handle, s, ev_bitmask, &running_handles);

    curl_multi_socket_all(multi_handle, &running_handles);

    curl_multi_remove_handle(multi_handle, curl_handle);
    curl_easy_cleanup(curl_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}