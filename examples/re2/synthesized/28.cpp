// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::FilteredRE2::Add at filtered_re2.cc:51:29 in filtered_re2.h
// re2::FilteredRE2::Compile at filtered_re2.cc:70:19 in filtered_re2.h
// re2::FilteredRE2::NumRegexps at filtered_re2.h:90:7 in filtered_re2.h
// re2::FilteredRE2::GetRE2 at filtered_re2.h:93:14 in filtered_re2.h
// re2::FilteredRE2::NumRegexps at filtered_re2.h:90:7 in filtered_re2.h
// re2::FilteredRE2::FirstMatch at filtered_re2.cc:98:18 in filtered_re2.h
// re2::FilteredRE2::NumRegexps at filtered_re2.h:90:7 in filtered_re2.h
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
#include "re2/filtered_re2.h"
#include <vector>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    re2::FilteredRE2 filtered_re2;
    re2::RE2::Options options;
    std::vector<std::string> strings_to_match;
    std::vector<int> atoms;
    std::vector<int> matching_regexps;
    int id;

    // Add patterns
    for (size_t i = 0; i < Size; ++i) {
        std::string pattern(1, Data[i]);
        filtered_re2.Add(pattern, options, &id);
    }

    // Compile patterns
    filtered_re2.Compile(&strings_to_match);

    // Get RE2 objects
    for (int i = 0; i < filtered_re2.NumRegexps(); ++i) {
        const re2::RE2& re2_obj = filtered_re2.GetRE2(i);
    }

    // FirstMatch
    std::string text(Data, Data + Size);
    if (filtered_re2.NumRegexps() > 0) {
        int first_match = filtered_re2.FirstMatch(text, atoms);
    }

    // AllMatches
    if (filtered_re2.NumRegexps() > 0) {
        bool any_matches = filtered_re2.AllMatches(text, atoms, &matching_regexps);
    }

    return 0;
}