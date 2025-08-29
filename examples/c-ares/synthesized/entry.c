// This is the entry of 54 fuzz drivers:
// 14, 16, 17, 18, 21, 22, 23, 24, 25, 26, 27, 28, 29, 31, 33, 38, 39, 40, 41, 42, 
// 43, 44, 46, 48, 51, 55, 59, 66, 67, 74, 75, 76, 80, 84, 86, 87, 88, 89, 90, 91, 
// 94, 98, 103, 108, 110, 114, 119, 120, 124, 125, 128, 129, 131, 133
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <memory.h>

// Declarations of all fuzz drivers `LLVMFuzzerTestOneInput` functions
int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_55(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_88(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_89(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_91(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_108(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_110(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_114(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_119(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_120(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_124(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_125(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_128(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_129(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_131(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_133(const uint8_t *Data, size_t Size);

// Entry function
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
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
    switch (driverIndex % 54) {
        case 0:
            return LLVMFuzzerTestOneInput_14(remainData, remainSize);
        case 1:
            return LLVMFuzzerTestOneInput_16(remainData, remainSize);
        case 2:
            return LLVMFuzzerTestOneInput_17(remainData, remainSize);
        case 3:
            return LLVMFuzzerTestOneInput_18(remainData, remainSize);
        case 4:
            return LLVMFuzzerTestOneInput_21(remainData, remainSize);
        case 5:
            return LLVMFuzzerTestOneInput_22(remainData, remainSize);
        case 6:
            return LLVMFuzzerTestOneInput_23(remainData, remainSize);
        case 7:
            return LLVMFuzzerTestOneInput_24(remainData, remainSize);
        case 8:
            return LLVMFuzzerTestOneInput_25(remainData, remainSize);
        case 9:
            return LLVMFuzzerTestOneInput_26(remainData, remainSize);
        case 10:
            return LLVMFuzzerTestOneInput_27(remainData, remainSize);
        case 11:
            return LLVMFuzzerTestOneInput_28(remainData, remainSize);
        case 12:
            return LLVMFuzzerTestOneInput_29(remainData, remainSize);
        case 13:
            return LLVMFuzzerTestOneInput_31(remainData, remainSize);
        case 14:
            return LLVMFuzzerTestOneInput_33(remainData, remainSize);
        case 15:
            return LLVMFuzzerTestOneInput_38(remainData, remainSize);
        case 16:
            return LLVMFuzzerTestOneInput_39(remainData, remainSize);
        case 17:
            return LLVMFuzzerTestOneInput_40(remainData, remainSize);
        case 18:
            return LLVMFuzzerTestOneInput_41(remainData, remainSize);
        case 19:
            return LLVMFuzzerTestOneInput_42(remainData, remainSize);
        case 20:
            return LLVMFuzzerTestOneInput_43(remainData, remainSize);
        case 21:
            return LLVMFuzzerTestOneInput_44(remainData, remainSize);
        case 22:
            return LLVMFuzzerTestOneInput_46(remainData, remainSize);
        case 23:
            return LLVMFuzzerTestOneInput_48(remainData, remainSize);
        case 24:
            return LLVMFuzzerTestOneInput_51(remainData, remainSize);
        case 25:
            return LLVMFuzzerTestOneInput_55(remainData, remainSize);
        case 26:
            return LLVMFuzzerTestOneInput_59(remainData, remainSize);
        case 27:
            return LLVMFuzzerTestOneInput_66(remainData, remainSize);
        case 28:
            return LLVMFuzzerTestOneInput_67(remainData, remainSize);
        case 29:
            return LLVMFuzzerTestOneInput_74(remainData, remainSize);
        case 30:
            return LLVMFuzzerTestOneInput_75(remainData, remainSize);
        case 31:
            return LLVMFuzzerTestOneInput_76(remainData, remainSize);
        case 32:
            return LLVMFuzzerTestOneInput_80(remainData, remainSize);
        case 33:
            return LLVMFuzzerTestOneInput_84(remainData, remainSize);
        case 34:
            return LLVMFuzzerTestOneInput_86(remainData, remainSize);
        case 35:
            return LLVMFuzzerTestOneInput_87(remainData, remainSize);
        case 36:
            return LLVMFuzzerTestOneInput_88(remainData, remainSize);
        case 37:
            return LLVMFuzzerTestOneInput_89(remainData, remainSize);
        case 38:
            return LLVMFuzzerTestOneInput_90(remainData, remainSize);
        case 39:
            return LLVMFuzzerTestOneInput_91(remainData, remainSize);
        case 40:
            return LLVMFuzzerTestOneInput_94(remainData, remainSize);
        case 41:
            return LLVMFuzzerTestOneInput_98(remainData, remainSize);
        case 42:
            return LLVMFuzzerTestOneInput_103(remainData, remainSize);
        case 43:
            return LLVMFuzzerTestOneInput_108(remainData, remainSize);
        case 44:
            return LLVMFuzzerTestOneInput_110(remainData, remainSize);
        case 45:
            return LLVMFuzzerTestOneInput_114(remainData, remainSize);
        case 46:
            return LLVMFuzzerTestOneInput_119(remainData, remainSize);
        case 47:
            return LLVMFuzzerTestOneInput_120(remainData, remainSize);
        case 48:
            return LLVMFuzzerTestOneInput_124(remainData, remainSize);
        case 49:
            return LLVMFuzzerTestOneInput_125(remainData, remainSize);
        case 50:
            return LLVMFuzzerTestOneInput_128(remainData, remainSize);
        case 51:
            return LLVMFuzzerTestOneInput_129(remainData, remainSize);
        case 52:
            return LLVMFuzzerTestOneInput_131(remainData, remainSize);
        case 53:
            return LLVMFuzzerTestOneInput_133(remainData, remainSize);
        default:
            return 0;
    }
    return 0;
}
