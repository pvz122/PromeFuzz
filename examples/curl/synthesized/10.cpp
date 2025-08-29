// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_init at easy.c:351:7 in easy.h
// curl_mime_init at mime.c:1284:12 in curl.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_mime_addpart at mime.c:1318:16 in curl.h
// curl_mime_free at mime.c:1186:6 in curl.h
// curl_easy_cleanup at easy.c:848:6 in easy.h
// curl_mime_type at mime.c:1453:10 in curl.h
// curl_mime_encoder at mime.c:1470:10 in curl.h
// curl_mime_filedata at mime.c:1405:10 in curl.h
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
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    CURL *curl = curl_easy_init();
    if (!curl) return 0;

    curl_mime *mime = curl_mime_init(curl);
    if (!mime) {
        curl_easy_cleanup(curl);
        return 0;
    }

    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        return 0;
    }

    // Write fuzzing data to a dummy file
    std::ofstream dummy_file("./dummy_file", std::ios::binary);
    dummy_file.write(reinterpret_cast<const char*>(Data), Size);
    dummy_file.close();

    // Ensure the MIME type string is null-terminated
    char *mime_type = reinterpret_cast<char*>(malloc(Size + 1));
    if (mime_type) {
        memcpy(mime_type, Data, Size);
        mime_type[Size] = '\0';

        // Fuzz curl_mime_type
        curl_mime_type(part, mime_type);

        free(mime_type);
    }

    // Fuzz curl_mime_encoder
    curl_mime_encoder(part, "binary");

    // Fuzz curl_mime_filedata
    curl_mime_filedata(part, "./dummy_file");

    // Fuzz curl_mime_name
    curl_mime_name(part, "part_name");

    // Fuzz curl_mime_filename
    curl_mime_filename(part, "file.txt");

    // Cleanup
    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    return 0;
}