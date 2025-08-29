// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::ok at re2.h:307:8 in re2.h
// re2::RE2::Replace at re2.cc:445:11 in re2.h
// re2::RE2::GlobalReplace at re2.cc:467:10 in re2.h
// re2::RE2::PossibleMatchRange at re2.cc:592:11 in re2.h
// re2::RE2::NamedCapturingGroups at re2.cc:390:40 in re2.h
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
#include <map>

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);
    std::string pattern = "a+";
    std::string rewrite = "b";
    std::string str = input;
    std::string min, max;
    int maxlen = 100;

    re2::RE2 re(pattern);
    if (!re.ok()) return 0;

    re2::RE2::Replace(&str, re, rewrite);
    re2::RE2::GlobalReplace(&str, re, rewrite);
    re.PossibleMatchRange(&min, &max, maxlen);
    const std::map<std::string, int>& named_groups = re.NamedCapturingGroups();

    return 0;
}