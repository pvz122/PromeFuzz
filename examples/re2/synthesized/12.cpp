// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::Extract at re2.cc:537:11 in re2.h
// re2::RE2::Replace at re2.cc:445:11 in re2.h
// re2::RE2::GlobalReplace at re2.cc:467:10 in re2.h
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
#include <string>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);
    std::string pattern = "a+";
    std::string rewrite = "b";
    std::string output;

    re2::RE2 re(pattern);

    // Test RE2::Extract
    re2::RE2::Extract(input, re, rewrite, &output);

    // Test RE2::Replace
    re2::RE2::Replace(&input, re, rewrite);

    // Test RE2::GlobalReplace
    re2::RE2::GlobalReplace(&input, re, rewrite);

    return 0;
}