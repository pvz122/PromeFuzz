// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFGetTagListCount at tif_extension.c:34:5 in tiffio.h
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFIsByteSwapped at tif_open.c:884:5 in tiffio.h
// TIFFIsBigEndian at tif_open.c:899:5 in tiffio.h
// TIFFCreateEXIFDirectory at tif_dir.c:1731:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:235:5 in tiffio.h
// TIFFDeferStrileArrayWriting at tif_dirwrite.c:265:5 in tiffio.h
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

int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    TIFF *tif = TIFFOpen("./dummy_file", "w+");
    if (!tif) return 0;

    // Create EXIF Directory
    if (TIFFCreateEXIFDirectory(tif) == 0) {
        TIFFClose(tif);
        return 0;
    }

    // Write a directory
    TIFFWriteDirectory(tif);

    // Check byte order
    int isByteSwapped = TIFFIsByteSwapped(tif);
    int isBigEndian = TIFFIsBigEndian(tif);

    // Defer strip/tile array writing
    TIFFDeferStrileArrayWriting(tif);

    // Get tag list count
    int tagCount = TIFFGetTagListCount(tif);

    // Cleanup
    TIFFClose(tif);
    return 0;
}