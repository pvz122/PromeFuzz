// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getValue at value.hpp:1330:17 in value.hpp
// Exiv2::getUShort at types.hpp:229:10 in types.hpp
// Exiv2::makeSlice at slice.hpp:536:32 in slice.hpp
// Exiv2::toData at value.hpp:1388:15 in value.hpp
// Exiv2::us2Data at types.cpp:331:8 in types.hpp
// Exiv2::getULongLong at types.cpp:257:10 in types.hpp
// Exiv2::ull2Data at types.cpp:357:8 in types.hpp
#include <cstdint>
#include <cstring>
#include <vector>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

extern "C" int LLVMFuzzerTestOneInput_495(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
    Exiv2::byte buf[8];
    std::memcpy(buf, Data, 8);

    // Test getValue<uint16_t>
    uint16_t val16 = Exiv2::getValue<uint16_t>(buf, byteOrder);

    // Test getUShort with vector storage
    std::vector<Exiv2::byte> vec(buf, buf + 8);
    uint16_t ushortVal = Exiv2::getUShort(Exiv2::makeSlice(vec), byteOrder);

    // Test toData<uint16_t>
    Exiv2::byte outBuf16[2];
    size_t bytesWritten16 = Exiv2::toData(outBuf16, val16, byteOrder);

    // Test us2Data
    size_t us2DataBytes = Exiv2::us2Data(outBuf16, ushortVal, byteOrder);

    // Test getULongLong
    uint64_t ullVal = Exiv2::getULongLong(buf, byteOrder);

    // Test ull2Data
    Exiv2::byte outBuf64[8];
    size_t ull2DataBytes = Exiv2::ull2Data(outBuf64, ullVal, byteOrder);

    return 0;
}