// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_url at urlapi.c:1293:8 in urlapi.h
// curl_url_cleanup at urlapi.c:1298:6 in urlapi.h
// curl_url_set at urlapi.c:1630:11 in urlapi.h
// curl_url_get at urlapi.c:1339:11 in urlapi.h
// curl_free at escape.c:208:6 in curl.h
// curl_url_dup at urlapi.c:1315:8 in urlapi.h
// curl_url_cleanup at urlapi.c:1298:6 in urlapi.h
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
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    CURLU *url = curl_url();
    if (!url) return 0;

    // Randomly set a part of the URL
    CURLUPart part = static_cast<CURLUPart>(Data[0] % (CURLUPART_ZONEID + 1));
    char *input = reinterpret_cast<char*>(malloc(Size));
    if (!input) {
        curl_url_cleanup(url);
        return 0;
    }
    memcpy(input, Data, Size);
    input[Size - 1] = '\0';

    curl_url_set(url, part, input, 0);
    free(input);

    // Randomly get a part of the URL
    char *output = nullptr;
    curl_url_get(url, part, &output, 0);
    if (output) {
        curl_free(output);
    }

    // Duplicate the URL handle
    CURLU *dup_url = curl_url_dup(url);
    if (dup_url) {
        curl_url_cleanup(dup_url);
    }

    curl_url_cleanup(url);
    return 0;
}