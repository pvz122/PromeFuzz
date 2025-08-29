// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1112:15 in value.hpp
// Exiv2::ValueType<double>::toUint32 at value.hpp:1588:36 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32 at value.hpp:1615:39 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toUint32 at value.hpp:1606:38 in value.hpp
// Exiv2::ValueType<float>::toUint32 at value.hpp:1597:35 in value.hpp
// Exiv2::ValueType::read at value.hpp:1512:19 in value.hpp
// Exiv2::Exifdatum::setValue at exif.cpp:254:17 in exif.hpp
// Exiv2::Metadatum::toUint32 at metadatum.cpp:16:21 in metadatum.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/value.hpp>
#include <exiv2/metadatum.hpp>
#include <exiv2/exif.hpp>
#include <cstdint>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_599(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) {
        return 0;
    }

    try {
        // Test Exiv2::ValueType<double>::toUint32
        {
            double doubleValue;
            memcpy(&doubleValue, Data, sizeof(double));
            Exiv2::ValueType<double> doubleValType(doubleValue);
            doubleValType.toUint32();
        }

        // Test Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32
        if (Size >= sizeof(unsigned int) * 2) {
            unsigned int first, second;
            memcpy(&first, Data, sizeof(unsigned int));
            memcpy(&second, Data + sizeof(unsigned int), sizeof(unsigned int));
            Exiv2::ValueType<std::pair<unsigned int, unsigned int>> pairValType(std::make_pair(first, second));
            pairValType.toUint32();
        }

        // Test Exiv2::ValueType<std::pair<int, int>>::toUint32
        if (Size >= sizeof(int) * 2) {
            int first, second;
            memcpy(&first, Data, sizeof(int));
            memcpy(&second, Data + sizeof(int), sizeof(int));
            Exiv2::ValueType<std::pair<int, int>> intPairValType(std::make_pair(first, second));
            intPairValType.toUint32();
        }

        // Test Exiv2::ValueType<float>::toUint32
        if (Size >= sizeof(float)) {
            float floatValue;
            memcpy(&floatValue, Data, sizeof(float));
            Exiv2::ValueType<float> floatValType(floatValue);
            floatValType.toUint32();
        }

        // Test Exiv2::Metadatum::toUint32 through Exifdatum
        if (Size > 0) {
            Exiv2::ExifKey key("Exif.Image.Orientation");
            Exiv2::Exifdatum datum(key);
            Exiv2::UShortValue value;
            std::string buf(reinterpret_cast<const char*>(Data), Size);
            value.read(buf);
            datum.setValue(&value);
            datum.toUint32();
        }

    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}