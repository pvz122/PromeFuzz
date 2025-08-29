// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_init at easy.c:351:7 in easy.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_easy_setopt at setopt.c:3057:10 in easy.h
// curl_easy_setopt at setopt.c:3057:10 in easy.h
// curl_easy_perform at easy.c:827:10 in easy.h
// curl_easy_getinfo at easy.c:864:10 in easy.h
// curl_easy_getinfo at easy.c:864:10 in easy.h
// curl_easy_reset at easy.c:1087:6 in easy.h
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

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Write fuzzing data to a dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        curl_easy_cleanup(curl);
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Set options for the curl handle
    curl_easy_setopt(curl, CURLOPT_URL, "file://./dummy_file");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Perform the curl request
    CURLcode res = curl_easy_perform(curl);
    if (res == CURLE_OK) {
        // Retrieve information from the curl session
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

        double total_time = 0;
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total_time);
    }

    // Reset the curl handle for reuse
    curl_easy_reset(curl);

    // Clean up the curl handle
    curl_easy_cleanup(curl);

    return 0;
}