// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:235:5 in tiffio.h
// TIFFFdOpen at tif_unix.c:205:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "tiffio.h"

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    // Prepare a dummy file for testing
    const char *filename = "./dummy_file";
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) return 0;

    // Write input data to the file
    write(fd, Data, Size);
    lseek(fd, 0, SEEK_SET);

    // Open the TIFF file using the file descriptor
    TIFF *tif = TIFFFdOpen(fd, filename, "w");
    if (tif) {
        // Call TIFFWriteDirectory to write a directory
        TIFFWriteDirectory(tif);

        // Clean up and close the TIFF file
        TIFFClose(tif);
    }

    // Close the file descriptor
    close(fd);

    // Free the dummy file
    unlink(filename);
    
    return 0;
}