// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_global_trace at easy.c:313:10 in curl.h
// curl_global_init_mem at easy.c:234:10 in curl.h
// curl_global_sslset at easy.c:333:12 in curl.h
// curl_global_init at easy.c:218:10 in curl.h
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

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Ensure the input is null-terminated for curl_global_trace
    std::vector<char> trace_config(Data, Data + Size);
    trace_config.push_back('\0');

    // Fuzz curl_global_trace
    curl_global_trace(trace_config.data());

    // Fuzz curl_global_init_mem
    curl_global_init_mem(CURL_GLOBAL_DEFAULT, nullptr, nullptr, nullptr, nullptr, nullptr);

    // Fuzz curl_global_sslset
    curl_sslbackend id = static_cast<curl_sslbackend>(Data[0] % 3);
    const char *name = "fuzz_backend";
    const curl_ssl_backend ***avail = nullptr;
    curl_global_sslset(id, name, avail);

    // Fuzz curl_global_init
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Cleanup
    curl_global_cleanup();

    return 0;
}