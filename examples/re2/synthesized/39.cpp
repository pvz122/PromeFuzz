// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::Octal at re2.h:964:22 in re2.h
// re2::RE2::Octal at re2.h:964:22 in re2.h
// re2::RE2::CRadix at re2.h:950:22 in re2.h
// re2::RE2::CRadix at re2.h:950:22 in re2.h
// re2::RE2::Hex at re2.h:957:22 in re2.h
// re2::RE2::Hex at re2.h:957:22 in re2.h
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

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    int value = *reinterpret_cast<const int*>(Data);
    int* ptr = &value;

    // Test RE2::Octal
    re2::RE2::Octal(ptr);
    re2::RE2::Octal<int>(ptr);

    // Test RE2::CRadix
    re2::RE2::CRadix(ptr);
    re2::RE2::CRadix<int>(ptr);

    // Test RE2::Hex
    re2::RE2::Hex(ptr);
    re2::RE2::Hex<int>(ptr);

    return 0;
}