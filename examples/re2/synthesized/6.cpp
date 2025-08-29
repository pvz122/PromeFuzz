// This fuzz driver is generated for library re2, aiming to fuzz the following functions:
// re2::RE2::ReverseProgramSize at re2.cc:324:10 in re2.h
// re2::RE2::ProgramFanout at re2.cc:374:10 in re2.h
// re2::RE2::ReverseProgramFanout at re2.cc:380:10 in re2.h
// re2::RE2::NumberOfCapturingGroups at re2.h:551:7 in re2.h
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
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string pattern(reinterpret_cast<const char*>(Data), Size);
    re2::RE2 regex(pattern);

    int reverseProgramSize = regex.ReverseProgramSize();
    if (reverseProgramSize == -1) return 0;

    std::vector<int> histogram;
    int programFanout = regex.ProgramFanout(&histogram);
    if (programFanout == -1) return 0;

    int reverseProgramFanout = regex.ReverseProgramFanout(&histogram);
    if (reverseProgramFanout == -1) return 0;

    int numberOfCapturingGroups = regex.NumberOfCapturingGroups();
    if (numberOfCapturingGroups == -1) return 0;

    return 0;
}