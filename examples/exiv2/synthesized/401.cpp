// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
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
#include <memory>

extern "C" int LLVMFuzzerTestOneInput_401(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Initialize with fuzz data
        Exiv2::ByteOrder byteOrder = static_cast<Exiv2::ByteOrder>(Data[0] % 3);
        Exiv2::TypeId typeId = static_cast<Exiv2::TypeId>(Data[0] % Exiv2::lastTypeId);
        const Exiv2::byte* buf = Data + 1;
        size_t len = Size - 1;

        // Create Value instance (base class)
        std::unique_ptr<Exiv2::Value> value(Exiv2::Value::create(typeId));
        if (value.get() == nullptr) return 0;

        // Test size()
        value->size();
        value->sizeDataArea();

        // Test setDataArea()
        if (len > 0) {
            value->setDataArea(buf, len);
        }

        // Test copy()
        Exiv2::byte* copyBuf = new Exiv2::byte[len];
        value->copy(copyBuf, byteOrder);
        delete[] copyBuf;

        // Test sizeDataArea()
        value->sizeDataArea();

    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}