// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::Options::set_case_sensitive at re2.h:724:10 in re2.h
// re2::RE2::Options::set_never_capture at re2.h:721:10 in re2.h
// re2::RE2::Options::set_dot_nl at re2.h:718:10 in re2.h
// re2::RE2::Options::set_posix_syntax at re2.h:703:10 in re2.h
// re2::RE2::Options::ParseFlags at re2.cc:161:19 in re2.h
// re2::FilteredRE2::Add at filtered_re2.cc:51:29 in filtered_re2.h
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
#include "re2/re2.h"

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    re2::RE2::Options options;
    options.set_case_sensitive(Data[0] & 1);
    options.set_never_capture(Data[0] & 2);
    options.set_dot_nl(Data[0] & 4);
    options.set_posix_syntax(Data[0] & 8);

    int flags = options.ParseFlags();

    re2::FilteredRE2 filtered_re2;
    int id;
    std::string pattern(reinterpret_cast<const char*>(Data), Size);
    re2::RE2::ErrorCode error = filtered_re2.Add(pattern, options, &id);

    return 0;
}