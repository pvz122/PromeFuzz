// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_init at easy.c:351:7 in easy.h
// curl_mime_init at mime.c:1284:12 in curl.h
// curl_mime_addpart at mime.c:1318:16 in curl.h
// curl_mime_init at mime.c:1284:12 in curl.h
// curl_mime_subparts at mime.c:1585:10 in curl.h
// curl_mime_type at mime.c:1453:10 in curl.h
// curl_mime_data_cb at mime.c:1511:10 in curl.h
// curl_mime_name at mime.c:1343:10 in curl.h
// curl_mime_filename at mime.c:1360:10 in curl.h
// curl_mime_free at mime.c:1186:6 in curl.h
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

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    CURL *curl = curl_easy_init();
    if (!curl) return 0;

    curl_mime *mime = curl_mime_init(curl);
    curl_mimepart *part = curl_mime_addpart(mime);

    // Fuzz curl_mime_subparts
    curl_mime *subparts = curl_mime_init(curl);
    curl_mime_subparts(part, subparts);

    // Fuzz curl_mime_type
    char *mimetype = (char *)malloc(Size + 1);
    if (mimetype) {
        memcpy(mimetype, Data, Size);
        mimetype[Size] = '\0';
        curl_mime_type(part, mimetype);
        free(mimetype);
    }

    // Fuzz curl_mime_data_cb
    curl_mime_data_cb(part, Size, nullptr, nullptr, nullptr, nullptr);

    // Fuzz curl_mime_name
    char *name = (char *)malloc(Size + 1);
    if (name) {
        memcpy(name, Data, Size);
        name[Size] = '\0';
        curl_mime_name(part, name);
        free(name);
    }

    // Fuzz curl_mime_filename
    char *filename = (char *)malloc(Size + 1);
    if (filename) {
        memcpy(filename, Data, Size);
        filename[Size] = '\0';
        curl_mime_filename(part, filename);
        free(filename);
    }

    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    return 0;
}