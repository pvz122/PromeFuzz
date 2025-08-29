// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::Iptcdatum::toRational at iptc.cpp:148:21 in iptc.hpp
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::Iptcdatum::toRational at iptc.cpp:148:21 in iptc.hpp
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::Iptcdatum::toRational at iptc.cpp:148:21 in iptc.hpp
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::Iptcdatum::toRational at iptc.cpp:148:21 in iptc.hpp
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::Iptcdatum::toRational at iptc.cpp:148:21 in iptc.hpp
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::Iptcdatum::toRational at iptc.cpp:148:21 in iptc.hpp
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
#include <exiv2/iptc.hpp>
#include <cstdint>
#include <cstdlib>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_629(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a dummy IPTC key
    Exiv2::IptcKey key("Iptc.Envelope.ModelVersion");

    try {
        size_t index = 0;
        if (Size > 1) {
            index = Data[1] % 2; // Safe index (0 or 1)
        }

        switch (Data[0] % 6) {
            case 0: {
                Exiv2::DataValue val;
                if (Size >= 3) {
                    val.read(Data + 1, 2);
                    Exiv2::Iptcdatum datum(key, &val);
                    (void)datum.toRational(index);
                }
                break;
            }
            case 1: {
                Exiv2::DataValue val;
                if (Size >= 1 + sizeof(double)) {
                    val.read(Data + 1, sizeof(double));
                    Exiv2::Iptcdatum datum(key, &val);
                    (void)datum.toRational(index);
                }
                break;
            }
            case 2: {
                Exiv2::DataValue val;
                if (Size >= 1 + sizeof(float)) {
                    val.read(Data + 1, sizeof(float));
                    Exiv2::Iptcdatum datum(key, &val);
                    (void)datum.toRational(index);
                }
                break;
            }
            case 3: {
                Exiv2::DataValue val;
                if (Size >= 3) {
                    val.read(Data + 1, 2);
                    Exiv2::Iptcdatum datum(key, &val);
                    (void)datum.toRational(index);
                }
                break;
            }
            case 4: {
                Exiv2::DataValue val;
                if (Size >= 2) {
                    val.read(Data + 1, 1);
                    Exiv2::Iptcdatum datum(key, &val);
                    (void)datum.toRational(index);
                }
                break;
            }
            case 5: {
                Exiv2::DataValue val;
                if (Size >= 2) {
                    val.read(Data + 1, 1);
                    Exiv2::Iptcdatum datum(key, &val);
                    (void)datum.toRational(index);
                }
                break;
            }
        }
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}