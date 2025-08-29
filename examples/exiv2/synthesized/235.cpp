// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::IptcDataSets::application2RecordList at datasets.cpp:367:30 in datasets.hpp
// Exiv2::IptcDataSets::recordName at datasets.cpp:460:27 in datasets.hpp
// Exiv2::IptcDataSets::recordId at datasets.cpp:475:24 in datasets.hpp
// Exiv2::IptcDataSets::envelopeRecordList at datasets.cpp:363:30 in datasets.hpp
// Exiv2::IptcDataSets::dataSetRepeatable at datasets.cpp:439:20 in datasets.hpp
// Exiv2::IptcDataSets::dataSetName at datasets.cpp:411:27 in datasets.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/datasets.hpp>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_235(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Fuzz application2RecordList
    const Exiv2::DataSet* app2List = Exiv2::IptcDataSets::application2RecordList();
    (void)app2List;

    // Fuzz recordName
    uint16_t recordId1;
    memcpy(&recordId1, Data, sizeof(recordId1));
    std::string recName = Exiv2::IptcDataSets::recordName(recordId1);
    (void)recName;

    // Fuzz recordId
    std::string recNameStr(reinterpret_cast<const char*>(Data), std::min(Size, (size_t)100));
    try {
        uint16_t recId = Exiv2::IptcDataSets::recordId(recNameStr);
        (void)recId;
    } catch (...) {}

    // Fuzz envelopeRecordList
    const Exiv2::DataSet* envList = Exiv2::IptcDataSets::envelopeRecordList();
    (void)envList;

    // Fuzz dataSetRepeatable
    uint16_t number, recordId2;
    memcpy(&number, Data, sizeof(number));
    memcpy(&recordId2, Data + sizeof(number), sizeof(recordId2));
    bool repeatable = Exiv2::IptcDataSets::dataSetRepeatable(number, recordId2);
    (void)repeatable;

    // Fuzz dataSetName
    uint16_t number2, recordId3;
    memcpy(&number2, Data, sizeof(number2));
    memcpy(&recordId3, Data + sizeof(number2), sizeof(recordId3));
    std::string dsName = Exiv2::IptcDataSets::dataSetName(number2, recordId3);
    (void)dsName;

    return 0;
}