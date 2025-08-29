// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::FullMatch at re2.h:411:15 in re2.h
// re2::RE2::PartialMatch at re2.h:427:15 in re2.h
// re2::RE2::Consume at re2.h:445:15 in re2.h
// re2::RE2::FindAndConsume at re2.h:463:15 in re2.h
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

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);
    std::string pattern = ".*";
    re2::RE2 re(pattern);

    std::string captured;

    // FullMatch
    re2::RE2::FullMatch(input, re, &captured);

    // PartialMatch
    re2::RE2::PartialMatch(input, re, &captured);

    // Consume
    absl::string_view input_view(input);
    re2::RE2::Consume(&input_view, re, &captured);

    // FindAndConsume
    absl::string_view input_view2(input);
    re2::RE2::FindAndConsume(&input_view2, re, &captured);

    return 0;
}