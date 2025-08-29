// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_global_init at easy.c:218:10 in curl.h
// curl_easy_init at easy.c:351:7 in easy.h
// curl_global_cleanup at easy.c:276:6 in curl.h
// curl_formadd at formdata.c:696:14 in curl.h
// curl_mime_init at mime.c:1284:12 in curl.h
// curl_mime_addpart at mime.c:1318:16 in curl.h
// curl_mime_data at mime.c:1377:10 in curl.h
// curl_mime_filedata at mime.c:1405:10 in curl.h
// curl_formget at formdata.c:715:5 in curl.h
// curl_mime_free at mime.c:1186:6 in curl.h
// curl_formfree at formdata.c:749:6 in curl.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_global_cleanup at easy.c:276:6 in curl.h
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
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize curl
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    if (!curl) {
        curl_global_cleanup();
        return 0;
    }

    // Fuzz curl_formadd
    struct curl_httppost *formpost = nullptr;
    struct curl_httppost *lastptr = nullptr;
    curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "name", CURLFORM_COPYCONTENTS, "content", CURLFORM_END);

    // Fuzz curl_mime_data
    curl_mime *mime = curl_mime_init(curl);
    curl_mimepart *part = curl_mime_addpart(mime);
    curl_mime_data(part, reinterpret_cast<const char*>(Data), Size);

    // Fuzz curl_mime_filedata
    std::ofstream file("./dummy_file", std::ios::binary);
    file.write(reinterpret_cast<const char*>(Data), Size);
    file.close();
    curl_mime_filedata(part, "./dummy_file");

    // Fuzz curl_formget
    curl_formget(formpost, nullptr, [](void *arg, const char *buf, size_t len) -> size_t {
        return len;
    });

    // Cleanup
    curl_mime_free(mime);
    curl_formfree(formpost);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}