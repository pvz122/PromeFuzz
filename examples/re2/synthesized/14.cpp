// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::Options::case_sensitive at re2.h:723:10 in re2.h
// re2::RE2::Options::log_errors at re2.h:708:10 in re2.h
// re2::RE2::Options::never_capture at re2.h:720:10 in re2.h
// re2::RE2::Options::perl_classes at re2.h:726:10 in re2.h
// re2::RE2::Options::literal at re2.h:711:10 in re2.h
// re2::RE2::Options::posix_syntax at re2.h:702:10 in re2.h
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

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    re2::RE2::Options options;

    // Check case sensitivity
    bool case_sensitive = options.case_sensitive();

    // Check error logging
    bool log_errors = options.log_errors();

    // Check never capture
    bool never_capture = options.never_capture();

    // Check Perl classes
    bool perl_classes = options.perl_classes();

    // Check literal
    bool literal = options.literal();

    // Check POSIX syntax
    bool posix_syntax = options.posix_syntax();

    return 0;
}