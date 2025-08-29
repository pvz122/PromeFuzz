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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tiffio.h"

int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    // Prepare a valid TIFFCodec for fuzzing TIFFUnRegisterCODEC
    TIFFCodec *codec = (TIFFCodec *)malloc(sizeof(TIFFCodec));
    if (codec) {
        codec->name = "dummy_codec"; // Assign a valid name
        // Fuzzing TIFFUnRegisterCODEC
        TIFFUnRegisterCODEC(codec);
        free(codec); // Free after unregistering
    }

    // Fuzzing TIFFIsCODECConfigured
    uint16_t codec_id = (Size > 1) ? Data[0] : 0; // Use first byte of input
    TIFFIsCODECConfigured(codec_id);

    // Fuzzing TIFFFindCODEC
    const TIFFCodec *found_codec = TIFFFindCODEC(codec_id);
    if (found_codec) {
        // Optionally interact with the found codec
    }

    // Prepare a dummy TIFF handle for TIFFWriteEncodedStrip
    TIFF *tif = TIFFOpen("./dummy_file.tiff", "w");
    if (tif) {
        uint32_t strip = 0;
        tmsize_t cc = Size; // Use input size
        void *buf = malloc(cc);
        if (buf) {
            memcpy(buf, Data, cc);
            TIFFWriteEncodedStrip(tif, strip, buf, cc);
            free(buf);
        }
        TIFFClose(tif);
    }

    // Fuzzing TIFFRegisterCODEC
    TIFFRegisterCODEC(codec_id, "dummy_codec", NULL);

    // Fuzzing TIFFGetConfiguredCODECs
    TIFFCodec *codecs = TIFFGetConfiguredCODECs();
    if (codecs) {
        // Free the codecs list
        free(codecs);
    }

    return 0;
}