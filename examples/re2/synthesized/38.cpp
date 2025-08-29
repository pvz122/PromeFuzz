// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::Options::set_one_line at re2.h:733:10 in re2.h
// re2::RE2::Options::set_never_capture at re2.h:721:10 in re2.h
// re2::RE2::Options::set_literal at re2.h:712:10 in re2.h
// re2::RE2::Options::set_log_errors at re2.h:709:10 in re2.h
// re2::RE2::Options::set_dot_nl at re2.h:718:10 in re2.h
// re2::RE2::Options::Copy at re2.h:735:10 in re2.h
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

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    re2::RE2::Options options;
    bool b = Data[0] & 1;

    options.set_one_line(b);
    options.set_never_capture(b);
    options.set_literal(b);
    options.set_log_errors(b);
    options.set_dot_nl(b);

    re2::RE2::Options src_options;
    options.Copy(src_options);

    return 0;
}