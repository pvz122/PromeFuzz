// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::IptcData::findKey at iptc.cpp:252:30 in iptc.hpp
// Exiv2::IptcData::end at iptc.hpp:211:12 in iptc.hpp
// Exiv2::Iptcdatum::setValue at iptc.cpp:195:17 in iptc.hpp
// Exiv2::IptcData::add at iptc.cpp:234:15 in iptc.hpp
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
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    FuzzedDataProvider fdp(Data, Size);

    try {
        // Create dummy IptcKey
        std::string keyStr = fdp.ConsumeRandomLengthString();
        if (keyStr.empty()) {
            return 0;
        }
        Exiv2::IptcKey key(keyStr);

        // Create dummy Value
        std::string valueStr = fdp.ConsumeRandomLengthString();
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
        value->read(valueStr);

        // Create IptcData
        Exiv2::IptcData iptcData;

        // Find key
        Exiv2::IptcData::iterator it = iptcData.findKey(key);

        // Get end iterator
        Exiv2::IptcData::iterator endIt = iptcData.end();

        // Create Iptcdatum
        Exiv2::Iptcdatum datum(key, value.get());

        // Set value
        datum.setValue(value.get());

        // Add to IptcData
        iptcData.add(key, value.get());

    } catch (...) {
        // Catch all exceptions to prevent crashes
        return 0;
    }

    return 0;
}