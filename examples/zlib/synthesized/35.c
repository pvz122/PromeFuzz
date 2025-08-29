// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit_ at inflate.c:218:13 in zlib.h
// inflate at inflate.c:590:13 in zlib.h
// inflateEnd at inflate.c:1266:13 in zlib.h
// inflateUndermine at inflate.c:1483:13 in zlib.h
// inflateResetKeep at inflate.c:106:13 in zlib.h
// inflateSync at inflate.c:1375:13 in zlib.h
// inflateValidate at inflate.c:1498:13 in zlib.h
// inflateSyncPoint at inflate.c:1431:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void initialize_z_stream(z_streamp strm, const uint8_t *data, size_t size) {
    strm->zalloc = Z_NULL;
    strm->zfree = Z_NULL;
    strm->opaque = Z_NULL;
    strm->next_in = (Bytef *)data;
    strm->avail_in = size;
    strm->next_out = Z_NULL;
    strm->avail_out = 0;
}

int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    z_stream strm;
    int ret;

    // Initialize z_stream
    initialize_z_stream(&strm, data, size);

    // Call inflate
    ret = inflateInit(&strm);
    if (ret == Z_OK) {
        ret = inflate(&strm, Z_NO_FLUSH);
        inflateEnd(&strm);
    }

    // Call inflateUndermine
    if (size > 0) {
        ret = inflateUndermine(&strm, data[0] & 1);
    }

    // Call inflateResetKeep
    ret = inflateResetKeep(&strm);

    // Call inflateSync
    ret = inflateSync(&strm);

    // Call inflateValidate
    if (size > 0) {
        ret = inflateValidate(&strm, data[0] & 1);
    }

    // Call inflateSyncPoint
    ret = inflateSyncPoint(&strm);

    return 0;
}