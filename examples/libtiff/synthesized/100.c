// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFFlushData at tif_flush.c:146:5 in tiffio.h
// TIFFSetFileno at tif_open.c:818:5 in tiffio.h
// TIFFGetMode at tif_open.c:843:5 in tiffio.h
// TIFFSetMode at tif_open.c:848:5 in tiffio.h
// TIFFSetupStrips at tif_write.c:553:5 in tiffio.h
// TIFFWriteCheck at tif_write.c:600:5 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_100(const uint8_t *Data, size_t Size) {
    TIFF *tif = TIFFOpen("./dummy_file", "w");
    if (!tif) return 0;

    int mode = (Size > 0) ? Data[0] % 2 : 0;
    TIFFSetMode(tif, mode);

    int current_mode = TIFFGetMode(tif);
    TIFFFlushData(tif);
    TIFFSetupStrips(tif);

    int new_fd = (Size > 1) ? Data[1] : -1;
    int old_fd = TIFFSetFileno(tif, new_fd);

    char name_buf[101] = {0};
    const char *name = "test";
    if (Size > 2) {
        size_t name_len = (Size - 2) > 100 ? 100 : (Size - 2);
        memcpy(name_buf, &Data[2], name_len);
        name_buf[name_len] = '\0';
        name = name_buf;
    }
    
    if (tif) {
        TIFFWriteCheck(tif, 0, name);
    }

    TIFFClose(tif);
    return 0;
}