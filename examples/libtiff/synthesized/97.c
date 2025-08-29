// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFFileno at tif_open.c:813:5 in tiffio.h
// TIFFGetMode at tif_open.c:843:5 in tiffio.h
// TIFFFreeDirectory at tif_dir.c:1619:6 in tiffio.h
// TIFFCreateDirectory at tif_dir.c:1688:5 in tiffio.h
// TIFFRewriteDirectory at tif_dirwrite.c:480:5 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "tiffio.h"

int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    TIFF *tif = TIFFOpen("./dummy_file", "w+");
    if (!tif) return 0;

    TIFFGetMode(tif);
    TIFFCreateDirectory(tif);
    TIFFRewriteDirectory(tif);
    TIFFFileno(tif);
    TIFFFreeDirectory(tif);

    TIFFClose(tif);
    return 0;
}