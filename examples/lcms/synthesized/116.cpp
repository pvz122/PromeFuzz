// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsIT8Free at cmscgats.c:1165:16 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsIT8Alloc at cmscgats.c:1449:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsIT8SetDataFormat at cmscgats.c:1689:19 in lcms2.h
// cmsIT8SetComment at cmscgats.c:1517:19 in lcms2.h
// cmsIT8SetPropertyStr at cmscgats.c:1528:19 in lcms2.h
// cmsIT8SetSheetType at cmscgats.c:1508:19 in lcms2.h
// cmsIT8SetPropertyMulti at cmscgats.c:1565:19 in lcms2.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <lcms2.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_116(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext ctx = cmsCreateContext(nullptr, nullptr);
    cmsHANDLE hIT8 = cmsIT8Alloc(ctx);
    if (!hIT8) {
        cmsDeleteContext(ctx);
        return 0;
    }

    // Randomly select a function to fuzz
    int func_choice = Data[0] % 5;
    Data++;
    Size--;

    switch (func_choice) {
        case 0: {
            if (Size < 1) break;
            int n = Data[0] % 256;
            Data++;
            Size--;
            if (Size < 1) break;
            char sample[256];
            size_t sample_len = Size < 255 ? Size : 255;
            memcpy(sample, Data, sample_len);
            sample[sample_len] = '\0';
            cmsIT8SetDataFormat(hIT8, n, sample);
            break;
        }
        case 1: {
            if (Size < 1) break;
            char comment[256];
            size_t comment_len = Size < 255 ? Size : 255;
            memcpy(comment, Data, comment_len);
            comment[comment_len] = '\0';
            cmsIT8SetComment(hIT8, comment);
            break;
        }
        case 2: {
            if (Size < 2) break;
            size_t prop_len = Size / 2;
            if (prop_len < 1) break;
            char prop[256];
            size_t prop_copy_len = prop_len < 255 ? prop_len : 255;
            memcpy(prop, Data, prop_copy_len);
            prop[prop_copy_len] = '\0';
            char str[256];
            size_t str_len = Size - prop_len;
            if (str_len < 1) break;
            size_t str_copy_len = str_len < 255 ? str_len : 255;
            memcpy(str, Data + prop_len, str_copy_len);
            str[str_copy_len] = '\0';
            cmsIT8SetPropertyStr(hIT8, prop, str);
            break;
        }
        case 3: {
            if (Size < 1) break;
            char type[256];
            size_t type_len = Size < 255 ? Size : 255;
            memcpy(type, Data, type_len);
            type[type_len] = '\0';
            cmsIT8SetSheetType(hIT8, type);
            break;
        }
        case 4: {
            if (Size < 3) break;
            size_t key_len = Size / 3;
            if (key_len < 1) break;
            char key[256];
            size_t key_copy_len = key_len < 255 ? key_len : 255;
            memcpy(key, Data, key_copy_len);
            key[key_copy_len] = '\0';
            size_t subkey_len = Size / 3;
            if (subkey_len < 1) break;
            char subkey[256];
            size_t subkey_copy_len = subkey_len < 255 ? subkey_len : 255;
            memcpy(subkey, Data + key_len, subkey_copy_len);
            subkey[subkey_copy_len] = '\0';
            char buffer[256];
            size_t buffer_len = Size - key_len - subkey_len;
            if (buffer_len < 1) break;
            size_t buffer_copy_len = buffer_len < 255 ? buffer_len : 255;
            memcpy(buffer, Data + key_len + subkey_len, buffer_copy_len);
            buffer[buffer_copy_len] = '\0';
            cmsIT8SetPropertyMulti(hIT8, key, subkey, buffer);
            break;
        }
    }

    cmsIT8Free(hIT8);
    cmsDeleteContext(ctx);
    return 0;
}