// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::Options::dot_nl at re2.h:717:10 in re2.h
// re2::RE2::Options::set_perl_classes at re2.h:727:10 in re2.h
// re2::RE2::Options::longest_match at re2.h:705:10 in re2.h
// re2::RE2::Options::never_nl at re2.h:714:10 in re2.h
// re2::RE2::Options::posix_syntax at re2.h:702:10 in re2.h
// re2::RE2::Options::set_one_line at re2.h:733:10 in re2.h
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

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    re2::RE2::Options options(re2::RE2::DefaultOptions);

    // Use the first byte to determine the value for boolean parameters
    bool b = Data[0] & 1;

    // Call the target API functions
    options.dot_nl();
    options.set_perl_classes(b);
    options.longest_match();
    options.never_nl();
    options.posix_syntax();
    options.set_one_line(b);

    return 0;
}