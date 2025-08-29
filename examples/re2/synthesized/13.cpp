// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::FullMatch at re2.h:411:15 in re2.h
// re2::RE2::Regexp at re2.h:340:16 in re2.h
// re2::RE2::FindAndConsume at re2.h:463:15 in re2.h
// re2::RE2::GlobalReplace at re2.cc:467:10 in re2.h
// re2::RE2::Consume at re2.h:445:15 in re2.h
// re2::RE2::PartialMatch at re2.h:427:15 in re2.h
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

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);
    std::string pattern = ".*";
    re2::RE2 re(pattern);

    std::string sub_pattern1;
    std::string sub_pattern2;

    // Test FullMatch
    re2::RE2::FullMatch(input, re, &sub_pattern1, &sub_pattern2);

    // Test Regexp
    re2::Regexp* regexp = re.Regexp();
    (void)regexp;

    // Test FindAndConsume
    absl::string_view input_view(input);
    re2::RE2::FindAndConsume(&input_view, re, &sub_pattern1, &sub_pattern2);

    // Test GlobalReplace
    std::string str = input;
    re2::RE2::GlobalReplace(&str, re, "replacement");

    // Test Consume
    absl::string_view consume_input(input);
    re2::RE2::Consume(&consume_input, re, &sub_pattern1, &sub_pattern2);

    // Test PartialMatch
    re2::RE2::PartialMatch(input, re, &sub_pattern1, &sub_pattern2);

    return 0;
}