// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_multi_init at multi.c:272:8 in multi.h
// curl_easy_init at easy.c:351:7 in easy.h
// curl_multi_cleanup at multi.c:2652:11 in multi.h
// curl_multi_add_handle at multi.c:294:11 in multi.h
// curl_multi_socket_action at multi.c:3038:11 in multi.h
// curl_multi_socket_action at multi.c:3038:11 in multi.h
// curl_multi_waitfds at multi.c:1042:11 in multi.h
// curl_multi_get_handles at multi.c:3445:8 in multi.h
// curl_multi_fdset at multi.c:990:11 in multi.h
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
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) return 0;

    CURL *easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    curl_multi_add_handle(multi_handle, easy_handle);

    int running_handles = 0;
    curl_socket_t sockfd = 0;
    int ev_bitmask = Data[0] % 3;

    curl_multi_socket_action(multi_handle, sockfd, ev_bitmask, &running_handles);

    curl_multi_socket(multi_handle, sockfd, &running_handles);

    struct curl_waitfd ufds[1];
    unsigned int fd_count = 0;
    curl_multi_waitfds(multi_handle, ufds, 1, &fd_count);

    CURL **handles = curl_multi_get_handles(multi_handle);
    if (handles) free(handles);

    fd_set read_fd_set, write_fd_set, exc_fd_set;
    int max_fd = 0;
    curl_multi_fdset(multi_handle, &read_fd_set, &write_fd_set, &exc_fd_set, &max_fd);

    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}