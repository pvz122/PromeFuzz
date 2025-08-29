// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_share_init at share.c:43:1 in curl.h
// curl_share_setopt at share.c:57:1 in curl.h
// curl_easy_strerror at strerror.c:56:1 in curl.h
// curl_multi_strerror at strerror.c:364:1 in multi.h
// curl_url_strerror at strerror.c:460:1 in urlapi.h
// curl_share_strerror at strerror.c:424:1 in curl.h
// curl_share_cleanup at share.c:223:1 in curl.h
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
#include <curl/urlapi.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a share handle
    CURLSH *share = curl_share_init();
    if (!share) return 0;

    // Fuzz curl_share_setopt with random options
    CURLSHoption option = static_cast<CURLSHoption>(Data[0] % CURLSHOPT_LAST);
    curl_share_setopt(share, option, nullptr);

    // Fuzz curl_easy_strerror with random CURLcode
    CURLcode easy_code = static_cast<CURLcode>(Data[0] % CURL_LAST);
    curl_easy_strerror(easy_code);

    // Fuzz curl_multi_strerror with random CURLMcode
    CURLMcode multi_code = static_cast<CURLMcode>(Data[0] % CURLM_LAST);
    curl_multi_strerror(multi_code);

    // Fuzz curl_url_strerror with random CURLUcode
    CURLUcode url_code = static_cast<CURLUcode>(Data[0] % CURLUE_LAST);
    curl_url_strerror(url_code);

    // Fuzz curl_share_strerror with random CURLSHcode
    CURLSHcode share_code = static_cast<CURLSHcode>(Data[0] % CURLSHE_LAST);
    curl_share_strerror(share_code);

    // Cleanup
    curl_share_cleanup(share);

    return 0;
}