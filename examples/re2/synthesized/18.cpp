// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::CheckRewriteString at re2.cc:966:11 in re2.h
// re2::RE2::Rewrite at re2.cc:1025:11 in re2.h
// re2::RE2::Replace at re2.cc:445:11 in re2.h
// re2::RE2::MaxSubmatch at re2.cc:1006:10 in re2.h
// re2::RE2::Extract at re2.cc:537:11 in re2.h
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
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);
    std::string rewrite = input.substr(0, Size / 2);
    std::string error;
    std::string out;
    re2::RE2::Options options;
    re2::RE2 re(input, options);

    // Test CheckRewriteString
    re.CheckRewriteString(rewrite, &error);

    // Test Rewrite
    absl::string_view vec[10];
    for (int i = 0; i < 10; ++i) {
        vec[i] = input;
    }
    re.Rewrite(&out, rewrite, vec, 10);

    // Test Replace
    std::string str = input;
    re2::RE2::Replace(&str, re, rewrite);

    // Test MaxSubmatch
    re2::RE2::MaxSubmatch(rewrite);

    // Test Extract
    re2::RE2::Extract(input, re, rewrite, &out);

    // Test GlobalReplace
    re2::RE2::GlobalReplace(&str, re, rewrite);

    return 0;
}