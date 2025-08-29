// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreateTransform at cmsxform.c:1348:32 in lcms2.h
// _cmsGetTransformWorkerFlags at cmsxform.c:801:27 in lcms2_plugin.h
// cmsGetTransformInputFormat at cmsxform.c:1422:27 in lcms2.h
// _cmsGetTransformFlags at cmsxform.c:780:27 in lcms2_plugin.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCreateProofingTransform at cmsxform.c:1391:25 in lcms2.h
// _cmsGetTransformWorkerFlags at cmsxform.c:801:27 in lcms2_plugin.h
// cmsGetTransformInputFormat at cmsxform.c:1422:27 in lcms2.h
// _cmsGetTransformFlags at cmsxform.c:780:27 in lcms2_plugin.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
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
#include <lcms2_plugin.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_109(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 8) return 0;

    cmsUInt32Number InputFormat = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsUInt32Number OutputFormat = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number));
    cmsUInt32Number Intent = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number) * 2);
    cmsUInt32Number dwFlags = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number) * 3);
    cmsUInt32Number ProofingIntent = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number) * 4);

    cmsHPROFILE InputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE OutputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE ProofingProfile = cmsCreate_sRGBProfile();

    cmsHTRANSFORM transform = cmsCreateTransform(InputProfile, InputFormat, OutputProfile, OutputFormat, Intent, dwFlags);
    if (transform) {
        _cmsGetTransformWorkerFlags(reinterpret_cast<_cmstransform_struct*>(transform));
        cmsGetTransformInputFormat(transform);
        _cmsGetTransformFlags(reinterpret_cast<_cmstransform_struct*>(transform));
        cmsDeleteTransform(transform);
    }

    cmsHTRANSFORM proofingTransform = cmsCreateProofingTransform(InputProfile, InputFormat, OutputProfile, OutputFormat, ProofingProfile, Intent, ProofingIntent, dwFlags);
    if (proofingTransform) {
        _cmsGetTransformWorkerFlags(reinterpret_cast<_cmstransform_struct*>(proofingTransform));
        cmsGetTransformInputFormat(proofingTransform);
        _cmsGetTransformFlags(reinterpret_cast<_cmstransform_struct*>(proofingTransform));
        cmsDeleteTransform(proofingTransform);
    }

    cmsCloseProfile(InputProfile);
    cmsCloseProfile(OutputProfile);
    cmsCloseProfile(ProofingProfile);

    return 0;
}