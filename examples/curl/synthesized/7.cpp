// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_multi_init at multi.c:272:8 in multi.h
// curl_easy_init at easy.c:351:7 in easy.h
// curl_multi_cleanup at multi.c:2652:11 in multi.h
// curl_share_init at share.c:43:1 in curl.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_multi_cleanup at multi.c:2652:11 in multi.h
// curl_multi_setopt at multi.c:2951:11 in multi.h
// curl_share_setopt at share.c:57:1 in curl.h
// curl_multi_remove_handle at multi.c:589:11 in multi.h
// curl_share_cleanup at share.c:223:1 in curl.h
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
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) return 0;

    CURL *curl_handle = curl_easy_init();
    if (!curl_handle) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    CURLSH *share_handle = curl_share_init();
    if (!share_handle) {
        curl_easy_cleanup(curl_handle);
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Fuzz curl_multi_setopt
    CURLMoption multi_option = static_cast<CURLMoption>(Data[0] % 100);
    curl_multi_setopt(multi_handle, multi_option, nullptr);

    // Fuzz curl_share_setopt
    CURLSHoption share_option = static_cast<CURLSHoption>(Data[0] % 100);
    curl_share_setopt(share_handle, share_option, nullptr);

    // Fuzz curl_multi_remove_handle
    curl_multi_remove_handle(multi_handle, curl_handle);

    // Clean up
    curl_share_cleanup(share_handle);
    curl_easy_cleanup(curl_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}