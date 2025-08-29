// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::pattern at re2.h:312:22 in re2.h
// re2::RE2::options at re2.h:758:18 in re2.h
// re2::RE2::Options::encoding at re2.h:699:14 in re2.h
// re2::RE2::pattern at re2.h:312:22 in re2.h
// re2::RE2::options at re2.h:758:18 in re2.h
// re2::RE2::Options::encoding at re2.h:699:14 in re2.h
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

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string pattern(reinterpret_cast<const char*>(Data), Size);
    re2::RE2 regex(pattern);

    const std::string& pattern1 = regex.pattern();
    const re2::RE2::Options& options1 = regex.options();
    re2::RE2::Options::Encoding encoding1 = options1.encoding();

    const std::string& pattern2 = regex.pattern();
    const re2::RE2::Options& options2 = regex.options();
    re2::RE2::Options::Encoding encoding2 = options2.encoding();

    return 0;
}