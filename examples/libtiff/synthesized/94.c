// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFFlush at tif_flush.c:30:5 in tiffio.h
// TIFFReadDirectory at tif_dirread.c:4233:5 in tiffio.h
// TIFFFileno at tif_open.c:813:5 in tiffio.h
// TIFFCreateDirectory at tif_dir.c:1688:5 in tiffio.h
// TIFFLastDirectory at tif_dir.c:2228:5 in tiffio.h
// TIFFRewriteDirectory at tif_dirwrite.c:480:5 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "tiffio.h"

int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size) {
    TIFF *tif = TIFFOpen("./dummy_file", "w+");
    if (!tif) {
        return 0;
    }

    // Fuzzing TIFFFlush
    TIFFFlush(tif);

    // Fuzzing TIFFCreateDirectory
    TIFFCreateDirectory(tif);

    // Fuzzing TIFFRewriteDirectory
    TIFFRewriteDirectory(tif);

    // Fuzzing TIFFFileno
    int fd = TIFFFileno(tif);

    // Fuzzing TIFFLastDirectory
    int lastDir = TIFFLastDirectory(tif);

    // Fuzzing TIFFReadDirectory
    TIFFReadDirectory(tif);

    // Cleanup
    TIFFClose(tif);
    return 0;
}