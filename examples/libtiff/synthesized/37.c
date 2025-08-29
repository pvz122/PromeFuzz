// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFReadDirectory at tif_dirread.c:4233:5 in tiffio.h
// TIFFCreateEXIFDirectory at tif_dir.c:1731:5 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2056:5 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1146:5 in tiffio.h
// TIFFCheckpointDirectory at tif_dirwrite.c:289:5 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    // Prepare a dummy TIFF file
    const char *filename = "./dummy_file";
    FILE *file = fopen(filename, "wb+");
    if (!file) return 0;

    // Write random data to the dummy file
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tif = TIFFOpen(filename, "r+");
    if (tif) {
        // Explore various states with the target functions
        uint64_t dir_offset = (Size > 8) ? *(uint64_t*)Data : 0;
        TIFFSetSubDirectory(tif, dir_offset);
        TIFFCreateEXIFDirectory(tif);
        TIFFSetField(tif, 0x010E, "Sample Image"); // ImageDescription
        TIFFCheckpointDirectory(tif);
        TIFFReadDirectory(tif);
        TIFFSetDirectory(tif, 0); // Attempt to set to the first directory

        // Clean up
        TIFFClose(tif);
    }

    // Remove the dummy file
    remove(filename);
    return 0;
}