// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::IptcData::add at iptc.cpp:234:15 in iptc.hpp
// Exiv2::IptcData::begin at iptc.hpp:207:12 in iptc.hpp
// Exiv2::IptcData::end at iptc.hpp:211:12 in iptc.hpp
// Exiv2::IptcData::findId at iptc.cpp:260:30 in iptc.hpp
// Exiv2::IptcData::empty at iptc.hpp:247:22 in iptc.hpp
// Exiv2::IptcData::end at iptc.hpp:211:12 in iptc.hpp
// Exiv2::IptcData::erase at iptc.cpp:274:30 in iptc.hpp
// Exiv2::IptcData::size at iptc.cpp:219:18 in iptc.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
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
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_239(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::IptcData iptcData;

        // Add some dummy data to the IptcData
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
        value->read(std::string("dummy_value"));
        Exiv2::IptcKey key("Iptc.Envelope.ModelVersion");
        iptcData.add(key, value.get());

        // Test begin() and end()
        auto it_begin = iptcData.begin();
        auto it_end = iptcData.end();

        // Test findId()
        uint16_t dataset = Data[0] % 100;
        uint16_t record = Exiv2::IptcDataSets::application2;
        auto it_find = iptcData.findId(dataset, record);

        // Test erase() if container is not empty
        if (!iptcData.empty() && it_begin != iptcData.end()) {
            iptcData.erase(it_begin);
        }

        // Test size()
        size_t data_size = iptcData.size();

        // Test add() with random data
        if (Size > 10) {
            std::string key_str(reinterpret_cast<const char*>(Data), 10);
            Exiv2::IptcKey new_key("Iptc." + key_str);
            Exiv2::Value::UniquePtr new_value = Exiv2::Value::create(Exiv2::asciiString);
            new_value->read(std::string(reinterpret_cast<const char*>(Data + 10), Size - 10));
            iptcData.add(new_key, new_value.get());
        }

    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}