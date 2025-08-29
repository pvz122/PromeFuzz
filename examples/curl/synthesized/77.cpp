// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_mime_init at mime.c:1284:12 in curl.h
// curl_mime_addpart at mime.c:1318:16 in curl.h
// curl_mime_free at mime.c:1186:6 in curl.h
// curl_mime_subparts at mime.c:1585:10 in curl.h
// curl_mime_data_cb at mime.c:1511:10 in curl.h
// curl_mime_encoder at mime.c:1470:10 in curl.h
// curl_mime_name at mime.c:1343:10 in curl.h
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
#include <string>

extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *Data, size_t Size) {
    curl_mime *mime = curl_mime_init(nullptr);
    if (!mime) return 0;

    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        return 0;
    }

    std::string input_str(reinterpret_cast<const char*>(Data), Size);
    const char* input = input_str.c_str();

    curl_mime_subparts(part, mime);
    curl_mime_data_cb(part, Size, nullptr, nullptr, nullptr, nullptr);
    curl_mime_encoder(part, input);
    curl_mime_name(part, input);
    curl_mime_filename(part, input);

    curl_mime_free(mime);
    return 0;
}