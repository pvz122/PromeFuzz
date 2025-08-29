// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_mime_init at mime.c:1284:12 in curl.h
// curl_mime_addpart at mime.c:1318:16 in curl.h
// curl_mime_free at mime.c:1186:6 in curl.h
// curl_mime_init at mime.c:1284:12 in curl.h
// curl_mime_subparts at mime.c:1585:10 in curl.h
// curl_mime_free at mime.c:1186:6 in curl.h
// curl_mime_type at mime.c:1453:10 in curl.h
// curl_mime_data_cb at mime.c:1511:10 in curl.h
// curl_mime_encoder at mime.c:1470:10 in curl.h
// curl_mime_filename at mime.c:1360:10 in curl.h
// curl_mime_free at mime.c:1186:6 in curl.h
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

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size) {
    curl_mime *mime = curl_mime_init(nullptr);
    if (!mime) return 0;

    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        return 0;
    }

    // Fuzz curl_mime_subparts
    curl_mime *submime = curl_mime_init(nullptr);
    if (submime) {
        curl_mime_subparts(part, submime);
        curl_mime_free(submime);
    }

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

    // Fuzz curl_mime_encoder
    char *encoding = (char *)malloc(Size + 1);
    if (encoding) {
        memcpy(encoding, Data, Size);
        encoding[Size] = '\0';
        curl_mime_encoder(part, encoding);
        free(encoding);
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
    return 0;
}