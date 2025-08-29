// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::IptcDataSets::dataSetList at datasets.cpp:490:20 in datasets.hpp
// Exiv2::ExifTags::isExifGroup at tags.cpp:101:16 in tags.hpp
// Exiv2::ExifTags::isMakerGroup at tags.cpp:96:16 in tags.hpp
// Exiv2::ExifTags::taglist at tags.cpp:138:16 in tags.hpp
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
#include <exiv2/tags.hpp>
#include <iostream>
#include <fstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file if needed (not used in this case)
    std::ofstream dummyFile("./dummy_file");
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    // Use first byte to determine group name
    std::string groupName(1, static_cast<char>(Data[0] % 128));

    // Invoke functions in specified order
    Exiv2::IptcDataSets::dataSetList(std::cout);
    Exiv2::ExifTags::isExifGroup(groupName);
    Exiv2::ExifTags::isMakerGroup(groupName);
    Exiv2::ExifTags::taglist(std::cout, groupName);

    return 0;
}