// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::Options::set_log_errors at re2.h:709:10 in re2.h
// re2::RE2::Options::set_encoding at re2.h:700:10 in re2.h
// re2::RE2::Options::set_posix_syntax at re2.h:703:10 in re2.h
// re2::RE2::Options::set_longest_match at re2.h:706:10 in re2.h
// re2::RE2::Options::set_literal at re2.h:712:10 in re2.h
// re2::RE2::Options::set_never_nl at re2.h:715:10 in re2.h
// re2::RE2::ok at re2.h:307:8 in re2.h
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

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    re2::RE2::Options options;
    options.set_log_errors(Data[0] & 1);
    options.set_encoding((Data[0] & 2) ? re2::RE2::Options::EncodingUTF8 : re2::RE2::Options::EncodingLatin1);
    options.set_posix_syntax(Data[0] & 4);
    options.set_longest_match(Data[0] & 8);
    options.set_literal(Data[0] & 16);
    options.set_never_nl(Data[0] & 32);

    const char* pattern = "dummy_pattern";
    re2::RE2 re(pattern, options);
    re.ok();

    return 0;
}