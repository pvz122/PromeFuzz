// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFCurrentDirOffset at tif_dir.c:2222:10 in tiffio.h
// TIFFCreateEXIFDirectory at tif_dir.c:1731:5 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1146:5 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
// TIFFSetWriteOffset at tif_write.c:956:6 in tiffio.h
// TIFFGetStrileOffset at tif_dirread.c:8347:10 in tiffio.h
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
#include "tiffio.h"

int LLVMFuzzerTestOneInput_158(const uint8_t *Data, size_t Size) {
    TIFF *tif;
    const char *dummy_file = "./dummy_file";
    uint32_t strile_index;
    uint64_t dir_offset;
    
    // Create a dummy TIFF file
    tif = TIFFOpen(dummy_file, "w+");
    if (!tif) return 0;

    // Fuzzing TIFFCreateEXIFDirectory
    if (TIFFCreateEXIFDirectory(tif) == 0) {
        TIFFClose(tif);
        return 0;
    }

    // Fuzzing TIFFSetField with random data
    uint32_t tag = (Size > 0) ? Data[0] % 0xFFFF : 0; // Random tag
    TIFFSetField(tif, tag, Data, Size);

    // Fuzzing TIFFCurrentDirOffset
    dir_offset = TIFFCurrentDirOffset(tif);

    // Fuzzing TIFFGetStrileOffset with a random index
    strile_index = (Size > 4) ? *(uint32_t *)Data % 100 : 0; // Random strile index
    TIFFGetStrileOffset(tif, strile_index);

    // Fuzzing TIFFSetSubDirectory with random offset
    TIFFSetSubDirectory(tif, dir_offset);

    // Fuzzing TIFFSetWriteOffset with random offset
    TIFFSetWriteOffset(tif, dir_offset + 100);

    // Cleanup
    TIFFClose(tif);
    return 0;
}