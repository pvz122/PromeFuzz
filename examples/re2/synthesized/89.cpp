// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::ok at re2.h:307:8 in re2.h
// re2::RE2::error_code at re2.h:320:13 in re2.h
// re2::RE2::NamedCapturingGroups at re2.cc:390:40 in re2.h
// re2::RE2::NumberOfCapturingGroups at re2.h:551:7 in re2.h
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
#include <cstdint>
#include <string>
#include <map>
#include <re2/re2.h>

extern "C" int LLVMFuzzerTestOneInput_89(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    std::string pattern(reinterpret_cast<const char*>(Data), Size);
    re2::RE2::Options options;
    re2::RE2 re(pattern, options);

    if (!re.ok()) {
        return 0;
    }

    if (re.error_code() != re2::RE2::NoError) {
        return 0;
    }

    const auto& named_groups = re.NamedCapturingGroups();
    int num_groups = re.NumberOfCapturingGroups();

    std::string text = "Sample text for matching.";
    std::string match_result;

    re2::RE2::PartialMatch(text, re, &match_result);

    return 0;
}