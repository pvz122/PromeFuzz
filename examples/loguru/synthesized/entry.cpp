// This is the entry of 31 fuzz drivers:
// 1, 6, 9, 12, 42, 65, 67, 70, 71, 73, 76, 77, 80, 81, 82, 84, 85, 87, 89, 90, 94,
//  96, 99, 100, 101, 104, 106, 107, 108, 109, 110
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <memory.h>

// Declarations of all fuzz drivers `LLVMFuzzerTestOneInput` functions
extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_73(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_89(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_99(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_100(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_101(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_104(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_106(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_107(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_108(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_109(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_110(const uint8_t *Data, size_t Size);

// Entry function
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    // Driver selector
    if (Size < 1) {
        return 0;
    }
    const uint8_t *selector = Data;
    unsigned int driverIndex = 0;
    memcpy(&driverIndex, selector, 1);

    // Remain data and size
    const uint8_t *remainData = Data + 1;
    size_t remainSize = Size - 1;
    if (remainSize == 0) {
        return 0;
    }

    // Select driver
    switch (driverIndex % 31) {
        case 0:
            return LLVMFuzzerTestOneInput_1(remainData, remainSize);
        case 1:
            return LLVMFuzzerTestOneInput_6(remainData, remainSize);
        case 2:
            return LLVMFuzzerTestOneInput_9(remainData, remainSize);
        case 3:
            return LLVMFuzzerTestOneInput_12(remainData, remainSize);
        case 4:
            return LLVMFuzzerTestOneInput_42(remainData, remainSize);
        case 5:
            return LLVMFuzzerTestOneInput_65(remainData, remainSize);
        case 6:
            return LLVMFuzzerTestOneInput_67(remainData, remainSize);
        case 7:
            return LLVMFuzzerTestOneInput_70(remainData, remainSize);
        case 8:
            return LLVMFuzzerTestOneInput_71(remainData, remainSize);
        case 9:
            return LLVMFuzzerTestOneInput_73(remainData, remainSize);
        case 10:
            return LLVMFuzzerTestOneInput_76(remainData, remainSize);
        case 11:
            return LLVMFuzzerTestOneInput_77(remainData, remainSize);
        case 12:
            return LLVMFuzzerTestOneInput_80(remainData, remainSize);
        case 13:
            return LLVMFuzzerTestOneInput_81(remainData, remainSize);
        case 14:
            return LLVMFuzzerTestOneInput_82(remainData, remainSize);
        case 15:
            return LLVMFuzzerTestOneInput_84(remainData, remainSize);
        case 16:
            return LLVMFuzzerTestOneInput_85(remainData, remainSize);
        case 17:
            return LLVMFuzzerTestOneInput_87(remainData, remainSize);
        case 18:
            return LLVMFuzzerTestOneInput_89(remainData, remainSize);
        case 19:
            return LLVMFuzzerTestOneInput_90(remainData, remainSize);
        case 20:
            return LLVMFuzzerTestOneInput_94(remainData, remainSize);
        case 21:
            return LLVMFuzzerTestOneInput_96(remainData, remainSize);
        case 22:
            return LLVMFuzzerTestOneInput_99(remainData, remainSize);
        case 23:
            return LLVMFuzzerTestOneInput_100(remainData, remainSize);
        case 24:
            return LLVMFuzzerTestOneInput_101(remainData, remainSize);
        case 25:
            return LLVMFuzzerTestOneInput_104(remainData, remainSize);
        case 26:
            return LLVMFuzzerTestOneInput_106(remainData, remainSize);
        case 27:
            return LLVMFuzzerTestOneInput_107(remainData, remainSize);
        case 28:
            return LLVMFuzzerTestOneInput_108(remainData, remainSize);
        case 29:
            return LLVMFuzzerTestOneInput_109(remainData, remainSize);
        case 30:
            return LLVMFuzzerTestOneInput_110(remainData, remainSize);
        default:
            return 0;
    }
    return 0;
}
