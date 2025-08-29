// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
#include <vector>
#include <cstdint>
#include <exiv2/exiv2.hpp>
#include <exiv2/value.hpp>

extern "C" int LLVMFuzzerTestOneInput_725(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    try {
        Exiv2::ByteOrder byteOrder = Exiv2::littleEndian;
        Exiv2::TypeId typeId = Exiv2::unsignedByte;

        // Create dummy buffer
        std::vector<unsigned char> buffer(Data, Data + Size);
        if (buffer.size() < 4) buffer.resize(4);

        // Create Value instances
        Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(typeId);
        val1->read(buffer.data(), buffer.size(), byteOrder);

        Exiv2::Value::UniquePtr val2 = Exiv2::Value::create(Exiv2::unsignedRational);
        val2->read(buffer.data(), buffer.size(), byteOrder);

        // Test API functions
        (void)val1->size();
        (void)val2->size();

        if (val1->count() > 0) {
            (void)val1->toRational(0);
            (void)val1->toUint32(0);
        }
        if (val2->count() > 0) {
            (void)val2->toRational(0);
            (void)val2->toUint32(0);
        }

        (void)val1->count();
        (void)val2->count();

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}