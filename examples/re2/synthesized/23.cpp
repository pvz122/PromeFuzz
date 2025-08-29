// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::FullMatch at re2.h:411:15 in re2.h
// re2::RE2::FullMatchN at re2.cc:413:11 in re2.h
// re2::RE2::NumberOfCapturingGroups at re2.h:551:7 in re2.h
// re2::RE2::NamedCapturingGroups at re2.cc:390:40 in re2.h
// re2::RE2::FindAndConsume at re2.h:463:15 in re2.h
// re2::RE2::Match at re2.cc:653:11 in re2.h
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
#include <map>

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);
    std::string pattern = ".*";
    re2::RE2 re(pattern);

    // Test FullMatch
    std::string sub1, sub2;
    re2::RE2::FullMatch(input, re, &sub1, &sub2);

    // Test FullMatchN
    re2::RE2::Arg arg1(&sub1), arg2(&sub2);
    const re2::RE2::Arg* args[] = { &arg1, &arg2 };
    re2::RE2::FullMatchN(input, re, args, 2);

    // Test NumberOfCapturingGroups
    re.NumberOfCapturingGroups();

    // Test NamedCapturingGroups
    re.NamedCapturingGroups();

    // Test FindAndConsume
    absl::string_view input_view(input);
    re2::RE2::FindAndConsume(&input_view, re, &sub1, &sub2);

    // Test Match
    absl::string_view submatch[2];
    re.Match(input, 0, input.size(), re2::RE2::UNANCHORED, submatch, 2);

    return 0;
}