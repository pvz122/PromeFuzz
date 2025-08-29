// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_init at easy.c:351:7 in easy.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_slist_append at slist.c:91:20 in curl.h
// curl_slist_free_all at slist.c:131:6 in curl.h
// curl_slist_append at slist.c:91:20 in curl.h
// curl_mime_headers at mime.c:1493:10 in curl.h
// curl_slist_free_all at slist.c:131:6 in curl.h
// curl_formfree at formdata.c:749:6 in curl.h
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
#include <curl/easy.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize CURL handle
    CURL *curl = curl_easy_init();
    if (!curl) return 0;

    // Cleanup CURL handle
    curl_easy_cleanup(curl);

    // Create a curl_slist and append data
    struct curl_slist *slist = nullptr;
    char *data = (char *)malloc(Size + 1);
    if (data) {
        memcpy(data, Data, Size);
        data[Size] = '\0';
        slist = curl_slist_append(slist, data);
        free(data);
    }

    // Free the curl_slist
    curl_slist_free_all(slist);

    // Create a curl_mimepart and set headers
    curl_mimepart *mimepart = nullptr;
    struct curl_slist *headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: text/plain");
    if (headers) {
        curl_mime_headers(mimepart, headers, 1);
        curl_slist_free_all(headers); // Free the headers after use
    }

    // Free the curl_form (deprecated)
    curl_formfree(nullptr);

    return 0;
}