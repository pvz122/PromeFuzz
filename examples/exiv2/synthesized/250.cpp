// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::IptcDataSets::dataSetList at datasets.cpp:490:20 in datasets.hpp
// Exiv2::Internal::MatroskaTag::dump at matroskavideo.hpp:89:8 in matroskavideo.hpp
// Exiv2::ExifTags::taglist at tags.cpp:114:16 in tags.hpp
// Exiv2::ExifTags::taglist at tags.cpp:138:16 in tags.hpp
// Exiv2::XmpProperties::printProperties at properties.cpp:5091:21 in properties.hpp
// Exiv2::DataValue::write at value.cpp:137:26 in value.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>

#include "properties.hpp"
#include "datasets.hpp"
#include "tags.hpp"
#include "value.hpp"
#include "matroskavideo.hpp"
#include "error.hpp"

extern "C" int LLVMFuzzerTestOneInput_250(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::ofstream dummy_file("./dummy_file", std::ios::binary);
    dummy_file.write(reinterpret_cast<const char*>(Data), Size);
    dummy_file.close();

    std::ostringstream oss;

    Exiv2::IptcDataSets::dataSetList(oss);

    {
        Exiv2::Internal::MatroskaTag tag(123, "test_label", Exiv2::Internal::String, Exiv2::Internal::Process);
        tag.dump(oss);
    }

    Exiv2::ExifTags::taglist(oss);
    std::string groupName(Data, Data + (Size % 32));
    Exiv2::ExifTags::taglist(oss, groupName);

    std::string prefix(Data, Data + (Size % 32));
    try {
        Exiv2::XmpProperties::printProperties(oss, prefix);
    } catch (const Exiv2::Error&) {}

    {
        std::vector<Exiv2::byte> buf(Data, Data + Size);
        Exiv2::DataValue value(buf.data(), buf.size());
        value.write(oss);
    }

    return 0;
}