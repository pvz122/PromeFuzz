// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::parseInt64 at types.cpp:534:9 in types.hpp
// Exiv2::parseFloat at types.cpp:568:7 in types.hpp
// Exiv2::parseRational at types.cpp:590:10 in types.hpp
// Exiv2::stringTo at types.hpp:483:3 in types.hpp
// Exiv2::stringTo at types.hpp:483:3 in types.hpp
// Exiv2::stringTo at types.cpp:517:6 in types.hpp
// Exiv2::toString at types.hpp:467:13 in types.hpp
// Exiv2::toString at types.hpp:467:13 in types.hpp
// Exiv2::toString at types.hpp:467:13 in types.hpp
// Exiv2::find at types.hpp:449:10 in types.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/types.hpp>
#include <string>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_363(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a string from the input data
    std::string input(reinterpret_cast<const char*>(Data), Size);

    // Test parseInt64
    bool ok = false;
    Exiv2::parseInt64(input, ok);

    // Test parseFloat
    Exiv2::parseFloat(input, ok);

    // Test parseRational
    Exiv2::parseRational(input, ok);

    // Test stringTo with different types
    Exiv2::stringTo<int>(input, ok);
    Exiv2::stringTo<float>(input, ok);
    Exiv2::stringTo<bool>(input, ok);

    // Test toString with different types
    Exiv2::toString(42);
    Exiv2::toString(3.14f);
    Exiv2::toString(true);

    // Test find function with a simple lookup table
    struct TestStruct {
        int key;
        const char* value;

        struct Key {
            Key(int k) : key(k) {}
            int key;
        };

        bool operator==(const Key& rhs) const {
            return key == rhs.key;
        }
    };

    const TestStruct testArray[] = {
        {1, "value1"},
        {2, "value2"},
        {3, "value3"}
    };

    int randomKey = Data[0] % 5; // Generate key from 0-4
    const TestStruct* found = Exiv2::find(testArray, TestStruct::Key(randomKey));

    return 0;
}