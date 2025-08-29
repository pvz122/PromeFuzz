// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::PartialMatchN at re2.cc:418:11 in re2.h
// re2::RE2::FindAndConsumeN at re2.cc:434:11 in re2.h
// re2::RE2::FullMatchN at re2.cc:413:11 in re2.h
// re2::RE2::FindAndConsume at re2.h:463:15 in re2.h
// re2::RE2::ConsumeN at re2.cc:423:11 in re2.h
// re2::RE2::Extract at re2.cc:537:11 in re2.h
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

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);
    absl::string_view input_view(input);

    re2::RE2::Options options;
    re2::RE2 re(".*", options);

    std::string out;
    re2::RE2::Arg arg1(&out);
    const re2::RE2::Arg* args[] = { &arg1 };

    re2::RE2::PartialMatchN(input_view, re, args, 1);
    re2::RE2::FindAndConsumeN(&input_view, re, args, 1);
    re2::RE2::FullMatchN(input_view, re, args, 1);
    re2::RE2::FindAndConsume(&input_view, re, &out);
    re2::RE2::ConsumeN(&input_view, re, args, 1);
    re2::RE2::Extract(input_view, re, ".*", &out);

    return 0;
}