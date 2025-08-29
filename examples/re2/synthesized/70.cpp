// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::Options::set_encoding at re2.h:700:10 in re2.h
// re2::FilteredRE2::Add at filtered_re2.cc:51:29 in filtered_re2.h
// re2::FilteredRE2::Compile at filtered_re2.cc:70:19 in filtered_re2.h
// re2::FilteredRE2::AllMatches at filtered_re2.cc:112:19 in filtered_re2.h
// re2::FilteredRE2::FirstMatch at filtered_re2.cc:98:18 in filtered_re2.h
// re2::FilteredRE2::SlowFirstMatch at filtered_re2.cc:91:18 in filtered_re2.h
// re2::FilteredRE2::NumRegexps at filtered_re2.h:90:7 in filtered_re2.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>
#include "filtered_re2.h"

extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size) {
    // Prepare input
    std::string input_text(reinterpret_cast<const char*>(Data), Size);
    re2::FilteredRE2 filtered_re2;
    std::vector<int> atoms;
    std::vector<int> matching_regexps;

    // Add patterns and compile
    for (int i = 0; i < 10; ++i) {
        std::string pattern = "pattern" + std::to_string(i);
        int id;
        re2::RE2::Options options;
        options.set_encoding(re2::RE2::Options::EncodingUTF8);
        filtered_re2.Add(pattern, options, &id);
        atoms.push_back(id);
    }

    // Compile the added patterns
    std::vector<std::string> strings_to_match;
    filtered_re2.Compile(&strings_to_match);

    // Test AllMatches
    filtered_re2.AllMatches(input_text, atoms, &matching_regexps);

    // Test FirstMatch
    filtered_re2.FirstMatch(input_text, atoms);

    // Test SlowFirstMatch
    filtered_re2.SlowFirstMatch(input_text);

    // Test NumRegexps
    int num_regexps = filtered_re2.NumRegexps();

    return 0;
}