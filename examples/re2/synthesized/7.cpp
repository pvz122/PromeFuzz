// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::ok at re2.h:307:8 in re2.h
// re2::RE2::CapturingGroupNames at re2.cc:401:40 in re2.h
// re2::RE2::QuoteMeta at re2.cc:554:18 in re2.h
// re2::RE2::Regexp at re2.h:340:16 in re2.h
// re2::RE2::Set::Add at set.cc:58:15 in set.h
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
#include "re2/set.h"
#include <map>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);

    // Create an RE2 object
    re2::RE2 re(input);
    if (!re.ok()) return 0;

    // Invoke CapturingGroupNames
    const std::map<int, std::string>& group_names = re.CapturingGroupNames();

    // Invoke QuoteMeta
    std::string quoted = re2::RE2::QuoteMeta(input);

    // Invoke Regexp
    re2::Regexp* regexp = re.Regexp();

    // Create an RE2::Set object
    re2::RE2::Set set(re2::RE2::Options(), re2::RE2::ANCHOR_BOTH);
    std::string error;

    // Invoke Set::Add
    set.Add(input, &error);

    return 0;
}