// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_init at easy.c:351:7 in easy.h
// curl_easy_ssls_export at easy.c:1375:10 in curl.h
// curl_easy_ssls_import at easy.c:1354:10 in curl.h
// curl_easy_reset at easy.c:1087:6 in easy.h
// curl_share_init at share.c:43:1 in curl.h
// curl_share_cleanup at share.c:223:1 in curl.h
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
#include <cstdint>
#include <cstdlib>
#include <cstring>

static CURLcode dummy_export_callback(void *userptr, void *session, const char *session_key, const unsigned char *shmac, size_t shmac_len, const unsigned char *sdata, size_t sdata_len, long timeout, int flags, const char *hostname, size_t hostname_len) {
    return CURLE_OK;
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    CURL *curl = curl_easy_init();
    if (!curl) return 0;

    // Fuzz curl_easy_ssls_export
    curl_easy_ssls_export(curl, dummy_export_callback, nullptr);

    // Fuzz curl_easy_ssls_import
    const char *session_key = nullptr;
    const unsigned char *shmac = nullptr;
    size_t shmac_len = 0;
    const unsigned char *sdata = Data;
    size_t sdata_len = Size;
    curl_easy_ssls_import(curl, session_key, shmac, shmac_len, sdata, sdata_len);

    // Fuzz curl_easy_reset
    curl_easy_reset(curl);

    // Fuzz curl_share_cleanup
    CURLSH *share = curl_share_init();
    if (share) {
        curl_share_cleanup(share);
    }

    curl_easy_cleanup(curl);

    return 0;
}