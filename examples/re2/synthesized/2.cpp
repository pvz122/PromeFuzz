// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::FilteredRE2::Add at filtered_re2.cc:51:29 in filtered_re2.h
// re2::FilteredRE2::Compile at filtered_re2.cc:70:19 in filtered_re2.h
// re2::RE2::Set::Add at set.cc:58:15 in set.h
// re2::RE2::Set::Compile at set.cc:97:16 in set.h
// re2::RE2::Set::Match at set.cc:127:16 in set.h
// re2::FilteredRE2::AllMatches at filtered_re2.cc:112:19 in filtered_re2.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "re2/set.h"
#include "re2/filtered_re2.h"
#include <vector>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);

    re2::RE2::Options options;
    re2::RE2::Set set(options, re2::RE2::Anchor::UNANCHORED);
    re2::FilteredRE2 filtered_re2;

    int id;
    re2::RE2::ErrorCode error_code = filtered_re2.Add(input, options, &id);
    if (error_code != re2::RE2::NoError) return 0;

    std::vector<std::string> strings_to_match;
    filtered_re2.Compile(&strings_to_match);

    std::string error;
    if (!set.Add(input, &error)) return 0;
    if (!set.Compile()) return 0;

    std::vector<int> matching_regexps;
    bool match_result = set.Match(input, &matching_regexps);

    std::vector<int> atoms = {0};
    bool all_matches_result = filtered_re2.AllMatches(input, atoms, &matching_regexps);

    return 0;
}