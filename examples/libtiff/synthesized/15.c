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

int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    // Initialize TIFFCodec structure
    TIFFCodec codec;
    memset(&codec, 0, sizeof(codec));

    // Fuzzing TIFFUnRegisterCODEC
    TIFFUnRegisterCODEC(&codec);

    // Fuzzing TIFFIsCODECConfigured
    if (Size >= sizeof(uint16_t)) {
        uint16_t codec_id = *(uint16_t *)Data;
        TIFFIsCODECConfigured(codec_id);
    }

    // Fuzzing TIFFFindCODEC
    if (Size >= sizeof(uint16_t)) {
        uint16_t codec_id = *(uint16_t *)Data;
        TIFFFindCODEC(codec_id);
    }

    // Prepare a dummy TIFF handle for TIFFWriteEncodedStrip
    TIFF *tif = TIFFOpen("./dummy_file", "w");
    if (tif) {
        uint32_t strip = 0;
        tmsize_t cc = Size; // Use the size of input data
        TIFFWriteEncodedStrip(tif, strip, (void *)Data, cc);
        TIFFClose(tif);
    }

    // Fuzzing TIFFRegisterCODEC
    if (Size >= sizeof(uint16_t) + 1) {
        uint16_t scheme = *(uint16_t *)Data;
        const char *method = (const char *)&Data[sizeof(uint16_t)];
        // Ensure method is null-terminated and fits within method_name
        char method_name[256];
        size_t method_length = strnlen((const char *)method, Size - sizeof(uint16_t));
        if (method_length >= sizeof(method_name)) {
            method_length = sizeof(method_name) - 1;
        }
        strncpy(method_name, method, method_length);
        method_name[method_length] = '\0';
        TIFFRegisterCODEC(scheme, method_name, NULL);
    }

    // Fuzzing TIFFGetConfiguredCODECs
    TIFFCodec *codecs = TIFFGetConfiguredCODECs();
    if (codecs) {
        free(codecs);
    }

    return 0;
}