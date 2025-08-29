// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::Options::set_encoding at re2.h:700:10 in re2.h
// re2::RE2::Options::set_posix_syntax at re2.h:703:10 in re2.h
// re2::RE2::Options::set_longest_match at re2.h:706:10 in re2.h
// re2::RE2::Options::set_log_errors at re2.h:709:10 in re2.h
// re2::RE2::Options::set_max_mem at re2.h:697:10 in re2.h
// re2::RE2::Options::set_literal at re2.h:712:10 in re2.h
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

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0;

    re2::RE2::Options options(re2::RE2::DefaultOptions);

    options.set_encoding(static_cast<re2::RE2::Options::Encoding>(Data[0] % 2 + 1));
    options.set_posix_syntax(Data[1] % 2);
    options.set_longest_match(Data[2] % 2);
    options.set_log_errors(Data[3] % 2);
    options.set_max_mem(static_cast<int64_t>(Data[4]) * 1024);
    options.set_literal(Data[5] % 2);

    return 0;
}