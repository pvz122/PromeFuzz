// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::Hex at re2.h:957:22 in re2.h
// re2::RE2::Hex at re2.h:957:22 in re2.h
// re2::RE2::CRadix at re2.h:950:22 in re2.h
// re2::RE2::CRadix at re2.h:950:22 in re2.h
// re2::RE2::Octal at re2.h:964:22 in re2.h
// re2::RE2::Octal at re2.h:964:22 in re2.h
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

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    int value;
    memcpy(&value, Data, sizeof(int));

    // Invoke RE2::Hex overloads
    re2::RE2::Hex(&value);
    re2::RE2::Hex<int>(&value);

    // Invoke RE2::CRadix overloads
    re2::RE2::CRadix(&value);
    re2::RE2::CRadix<int>(&value);

    // Invoke RE2::Octal overloads
    re2::RE2::Octal(&value);
    re2::RE2::Octal<int>(&value);

    return 0;
}