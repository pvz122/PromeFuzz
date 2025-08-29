// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFRawStripSize64 at tif_strip.c:152:10 in tiffio.h
// TIFFVStripSize64 at tif_strip.c:87:10 in tiffio.h
// TIFFDefaultStripSize at tif_strip.c:217:10 in tiffio.h
// TIFFCurrentStrip at tif_open.c:874:10 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
// TIFFComputeStrip at tif_strip.c:35:10 in tiffio.h
// TIFFNumberOfStrips at tif_strip.c:64:10 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_151(const uint8_t *Data, size_t Size) {
    // Create a dummy TIFF file
    const char *filename = "./dummy_file";
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) return 0;

    // Write random data to the dummy file
    write(fd, Data, Size);
    close(fd);

    // Open the TIFF file
    TIFF *tif = TIFFOpen(filename, "r");
    if (tif) {
        // Fuzzing TIFFCurrentStrip
        TIFFCurrentStrip(tif);

        // Fuzzing TIFFDefaultStripSize
        TIFFDefaultStripSize(tif, 0);

        // Fuzzing TIFFVStripSize64
        TIFFVStripSize64(tif, 1);

        // Fuzzing TIFFNumberOfStrips
        TIFFNumberOfStrips(tif);

        // Fuzzing TIFFComputeStrip
        TIFFComputeStrip(tif, 0, 0);

        // Fuzzing TIFFRawStripSize64
        TIFFRawStripSize64(tif, 0);

        // Close the TIFF file
        TIFFClose(tif);
    }

    // Remove the dummy file
    unlink(filename);
    return 0;
}