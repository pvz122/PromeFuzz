// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_multi_init at multi.c:272:8 in multi.h
// curl_easy_init at easy.c:351:7 in easy.h
// curl_multi_cleanup at multi.c:2652:11 in multi.h
// curl_multi_setopt at multi.c:2951:11 in multi.h
// curl_multi_add_handle at multi.c:294:11 in multi.h
// curl_pushheader_bynum at http2.c:2959:7 in multi.h
// curl_pushheader_byname at http2.c:2966:7 in multi.h
// curl_multi_strerror at strerror.c:364:1 in multi.h
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

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) return 0;

    CURL *curl_handle = curl_easy_init();
    if (!curl_handle) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Fuzz curl_multi_setopt
    CURLMoption option = static_cast<CURLMoption>(Data[0] % 10);
    curl_multi_setopt(multi_handle, option, nullptr);

    // Fuzz curl_multi_add_handle
    curl_multi_add_handle(multi_handle, curl_handle);

    // Fuzz curl_pushheader_bynum and curl_pushheader_byname
    struct curl_pushheaders *push_headers = nullptr;
    if (Size > 1) {
        size_t num = Data[1] % Size;
        curl_pushheader_bynum(push_headers, num);
        const char *name = reinterpret_cast<const char*>(Data + num);
        curl_pushheader_byname(push_headers, name);
    }

    // Fuzz curl_multi_strerror
    CURLMcode code = static_cast<CURLMcode>(Data[0] % 10);
    curl_multi_strerror(code);

    curl_easy_cleanup(curl_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}