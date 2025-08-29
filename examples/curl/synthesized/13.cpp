// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_multi_init at multi.c:272:8 in multi.h
// curl_multi_poll at multi.c:1350:11 in multi.h
// curl_multi_wakeup at multi.c:1360:11 in multi.h
// curl_multi_wait at multi.c:1340:11 in multi.h
// curl_multi_assign at multi.c:3378:11 in multi.h
// curl_multi_perform at multi.c:2552:11 in multi.h
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
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) return 0;

    int timeout_ms = *(int *)Data;
    int ret;
    struct curl_waitfd extra_fds[1];
    extra_fds[0].fd = 0;
    extra_fds[0].events = CURL_WAIT_POLLIN;
    extra_fds[0].revents = 0;

    curl_multi_poll(multi_handle, extra_fds, 1, timeout_ms, &ret);
    curl_multi_wakeup(multi_handle);
    curl_multi_wait(multi_handle, extra_fds, 1, timeout_ms, &ret);

    curl_socket_t sockfd = 0;
    void *sockp = nullptr;
    curl_multi_assign(multi_handle, sockfd, sockp);

    int running_handles;
    curl_multi_perform(multi_handle, &running_handles);

    curl_multi_cleanup(multi_handle);
    return 0;
}