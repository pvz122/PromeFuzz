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
#include <curl/urlapi.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    CURLU *handle = curl_url();
    if (!handle) return 0;

    // Randomly choose a CURLUPart to set/get
    CURLUPart part = static_cast<CURLUPart>(Data[0] % (CURLUPART_ZONEID + 1));

    // Set a part
    char *input = reinterpret_cast<char *>(malloc(Size));
    if (!input) {
        curl_url_cleanup(handle);
        return 0;
    }
    memcpy(input, Data, Size);
    input[Size - 1] = '\0';
    CURLUcode set_result = curl_url_set(handle, part, input, 0);
    free(input);

    // Get the part
    char *output = nullptr;
    CURLUcode get_result = curl_url_get(handle, part, &output, 0);
    if (output) curl_free(output);

    // Clean up
    curl_url_cleanup(handle);

    return 0;
}