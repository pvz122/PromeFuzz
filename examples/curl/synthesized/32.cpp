// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_multi_init at multi.c:272:8 in multi.h
// curl_easy_init at easy.c:351:7 in easy.h
// curl_multi_cleanup at multi.c:2652:11 in multi.h
// curl_multi_add_handle at multi.c:294:11 in multi.h
// curl_multi_info_read at multi.c:2731:10 in multi.h
// curl_multi_socket_action at multi.c:3038:11 in multi.h
// curl_version_info at version.c:604:25 in curl.h
// curl_multi_wait at multi.c:1340:11 in multi.h
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
#include <curl/curl.h>
#include <curl/multi.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) return 0;

    CURL *easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    curl_multi_add_handle(multi_handle, easy_handle);

    int msgs_in_queue = 0;
    CURLMsg *msg = curl_multi_info_read(multi_handle, &msgs_in_queue);

    curl_socket_t sockfd = (curl_socket_t)(Data[0] % 1024);
    int running_handles = 0;
    curl_multi_socket_action(multi_handle, sockfd, 0, &running_handles);

    curl_version_info_data *version_info = curl_version_info(CURLVERSION_NOW);

    struct curl_waitfd extra_fds[1];
    extra_fds[0].fd = sockfd;
    extra_fds[0].events = CURL_WAIT_POLLIN;
    extra_fds[0].revents = 0;
    int ret = 0;
    curl_multi_wait(multi_handle, extra_fds, 1, 1000, &ret);

    curl_multi_socket_all(multi_handle, &running_handles);

    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}