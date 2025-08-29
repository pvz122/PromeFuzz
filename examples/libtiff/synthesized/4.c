// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    const char *filename = "./dummy_file";
    FILE *file = fopen(filename, "wb+");
    if (file == NULL) {
        return 0;
    }

    fwrite(Data, 1, Size, file);
    fclose(file);

    /* Use "rh" mode to enable TIFF_HEADERONLY flag */
    TIFF *tif = TIFFOpen(filename, "rh");
    if (tif == NULL) {
        return 0;
    }

    /* Prevent directory parsing operations */
    TIFFClose(tif);
    unlink(filename);
    return 0;
}