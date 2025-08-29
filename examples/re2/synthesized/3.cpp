// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::Options::set_never_nl at re2.h:715:10 in re2.h
// re2::RE2::Options::set_dot_nl at re2.h:718:10 in re2.h
// re2::RE2::Options::set_never_capture at re2.h:721:10 in re2.h
// re2::RE2::Options::set_case_sensitive at re2.h:724:10 in re2.h
// re2::RE2::Options::set_perl_classes at re2.h:727:10 in re2.h
// re2::RE2::Options::set_word_boundary at re2.h:730:10 in re2.h
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

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < 7) return 0;

    re2::RE2::Options options(re2::RE2::DefaultOptions);

    options.set_never_nl(Data[0] & 1);
    options.set_dot_nl(Data[1] & 1);
    options.set_never_capture(Data[2] & 1);
    options.set_case_sensitive(Data[3] & 1);
    options.set_perl_classes(Data[4] & 1);
    options.set_word_boundary(Data[5] & 1);
    options.set_one_line(Data[6] & 1);

    return 0;
}