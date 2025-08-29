// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::IptcDataSets::dataSet at datasets.cpp:446:24 in datasets.hpp
// Exiv2::IptcDataSets::recordName at datasets.cpp:460:27 in datasets.hpp
// Exiv2::IptcDataSets::dataSetName at datasets.cpp:411:27 in datasets.hpp
// Exiv2::IptcDataSets::dataSetPsName at datasets.cpp:432:27 in datasets.hpp
// Exiv2::IptcDataSets::recordId at datasets.cpp:475:24 in datasets.hpp
// Exiv2::IptcDataSets::dataSetDesc at datasets.cpp:425:27 in datasets.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/iptc.hpp>
#include <string>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Extract recordId and number from input data
    uint16_t recordId = (Data[0] << 8) | Data[1];
    uint16_t number = (Size > 3) ? ((Data[2] << 8) | Data[3]) : 0;
    std::string dataSetName(reinterpret_cast<const char*>(Data), Size);

    try {
        // Test dataSet function
        (void)Exiv2::IptcDataSets::dataSet(dataSetName, recordId);

        // Test recordName function
        (void)Exiv2::IptcDataSets::recordName(recordId);

        // Test dataSetName function
        (void)Exiv2::IptcDataSets::dataSetName(number, recordId);

        // Test dataSetPsName function
        (void)Exiv2::IptcDataSets::dataSetPsName(number, recordId);

        // Test recordId function
        (void)Exiv2::IptcDataSets::recordId(dataSetName);

        // Test dataSetDesc function
        (void)Exiv2::IptcDataSets::dataSetDesc(number, recordId);
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}