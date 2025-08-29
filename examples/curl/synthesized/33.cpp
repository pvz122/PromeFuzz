// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_url at urlapi.c:1293:8 in urlapi.h
// curl_url_cleanup at urlapi.c:1298:6 in urlapi.h
// curl_url_set at urlapi.c:1630:11 in urlapi.h
// curl_url_get at urlapi.c:1339:11 in urlapi.h
// curl_free at escape.c:208:6 in curl.h
// curl_url_cleanup at urlapi.c:1298:6 in urlapi.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "urlapi.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    CURLU *url = curl_url();
    if (!url) return 0;

    // Generate a dummy URL part from the input data
    char *part = (char *)malloc(Size + 1);
    if (!part) {
        curl_url_cleanup(url);
        return 0;
    }
    memcpy(part, Data, Size);
    part[Size] = '\0';

    // Randomly choose a CURLUPart to set and get
    CURLUPart what = static_cast<CURLUPart>(Data[0] % (CURLUPART_ZONEID + 1));

    // Set the URL part
    CURLUcode set_code = curl_url_set(url, what, part, 0);
    if (set_code == CURLUE_OK) {
        // Get the URL part
        char *retrieved_part = nullptr;
        CURLUcode get_code = curl_url_get(url, what, &retrieved_part, 0);
        if (get_code == CURLUE_OK && retrieved_part) {
            curl_free(retrieved_part);
        }
    }

    free(part);
    curl_url_cleanup(url);
    return 0;
}