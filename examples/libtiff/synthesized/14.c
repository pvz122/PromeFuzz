// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFFindCODEC at tif_compress.c:192:18 in tiffio.h
// TIFFRegisterCODEC at tif_compress.c:206:12 in tiffio.h
// TIFFUnRegisterCODEC at tif_compress.c:232:6 in tiffio.h
// TIFFIsCODECConfigured at tif_codec.c:146:5 in tiffio.h
// TIFFGetConfiguredCODECs at tif_compress.c:261:12 in tiffio.h
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
// TIFFWriteEncodedStrip at tif_write.c:215:10 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    // Fuzzing TIFFRegisterCODEC
    TIFFRegisterCODEC(0, "FuzzCodec", NULL);

    // Fuzzing TIFFIsCODECConfigured
    TIFFIsCODECConfigured(0);

    // Fuzzing TIFFFindCODEC
    const TIFFCodec *foundCodec = TIFFFindCODEC(0);
    if (foundCodec) {
        // Fuzzing TIFFUnRegisterCODEC
        TIFFUnRegisterCODEC((TIFFCodec *)foundCodec);
    }

    // Prepare a dummy TIFF file for testing TIFFWriteEncodedStrip
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        TIFF *tif = TIFFOpen("./dummy_file", "w");
        if (tif) {
            uint32_t strip = 0;
            tmsize_t cc = Size < 1024 ? Size : 1024; // Limit size for testing
            TIFFWriteEncodedStrip(tif, strip, (void *)Data, cc);
            TIFFClose(tif);
        }
        fclose(file);
    }

    // Fuzzing TIFFGetConfiguredCODECs
    TIFFCodec *codecs = TIFFGetConfiguredCODECs();
    if (codecs) {
        // Free the codecs array
        free(codecs);
    }

    return 0;
}