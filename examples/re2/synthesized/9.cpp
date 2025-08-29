// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::ok at re2.h:307:8 in re2.h
// re2::RE2::error_code at re2.h:320:13 in re2.h
// re2::RE2::error at re2.h:316:22 in re2.h
// re2::RE2::error_arg at re2.h:324:22 in re2.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "re2/re2.h"
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string pattern(reinterpret_cast<const char*>(Data), Size);
    re2::RE2 regex(pattern);

    bool ok = regex.ok();
    re2::RE2::ErrorCode error_code = regex.error_code();
    const std::string& error = regex.error();
    const std::string& error_arg = regex.error_arg();

    return 0;
}