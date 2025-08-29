// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// _cmsCalloc at cmserr.c:279:17 in lcms2_plugin.h
// _cmsRealloc at cmserr.c:286:17 in lcms2_plugin.h
// _cmsDupMem at cmserr.c:302:17 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// _cmsMallocZero at cmserr.c:272:17 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// cmsMD5alloc at cmsmd5.c:154:21 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "lcms2_plugin.h"
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 2) return 0;

    cmsContext ContextID = cmsCreateContext(nullptr, nullptr);
    if (!ContextID) return 0;

    cmsUInt32Number num = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsUInt32Number size = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number));

    void* ptr1 = _cmsCalloc(ContextID, num, size);
    if (ptr1) {
        void* ptr2 = _cmsRealloc(ContextID, ptr1, size * 2);
        if (ptr2) {
            void* ptr3 = _cmsDupMem(ContextID, ptr2, size * 2);
            if (ptr3) {
                _cmsFree(ContextID, ptr3);
            }
            _cmsFree(ContextID, ptr2);
        } else {
            _cmsFree(ContextID, ptr1);
        }
    }

    void* ptr4 = _cmsMallocZero(ContextID, size);
    if (ptr4) {
        _cmsFree(ContextID, ptr4);
    }

    cmsHANDLE md5 = cmsMD5alloc(ContextID);
    if (md5) {
        _cmsFree(ContextID, md5);
    }

    cmsDeleteContext(ContextID);
    return 0;
}