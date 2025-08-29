// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_init at easy.c:351:7 in easy.h
// curl_multi_init at multi.c:272:8 in multi.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_easy_header at headers.c:62:11 in header.h
// curl_multi_setopt at multi.c:2951:11 in multi.h
// curl_multi_setopt at multi.c:2951:11 in multi.h
// curl_pushheader_bynum at http2.c:2959:7 in multi.h
// curl_pushheader_byname at http2.c:2966:7 in multi.h
// curl_version at version.c:170:7 in curl.h
// curl_multi_cleanup at multi.c:2652:11 in multi.h
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
#include <curl/header.h>
#include <curl/multi.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize CURL easy handle
    CURL *easy = curl_easy_init();
    if (!easy) return 0;

    // Initialize CURL multi handle
    CURLM *multi = curl_multi_init();
    if (!multi) {
        curl_easy_cleanup(easy);
        return 0;
    }

    // Fuzz curl_easy_header
    const char *name = "Content-Type";
    size_t index = 0;
    unsigned int origin = CURLH_HEADER;
    int request = 0;
    struct curl_header *hout = nullptr;
    curl_easy_header(easy, name, index, origin, request, &hout);

    // Fuzz curl_multi_setopt
    curl_multi_setopt(multi, CURLMOPT_SOCKETFUNCTION, nullptr);
    curl_multi_setopt(multi, CURLMOPT_PUSHFUNCTION, nullptr);

    // Fuzz curl_pushheader_bynum and curl_pushheader_byname
    struct curl_pushheaders *pushheaders = nullptr;
    curl_pushheader_bynum(pushheaders, 0);
    curl_pushheader_byname(pushheaders, "Accept");

    // Fuzz curl_version
    curl_version();

    // Cleanup
    curl_multi_cleanup(multi);
    curl_easy_cleanup(easy);

    return 0;
}