// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFErrorExt at tif_error.c:63:6 in tiffio.h
// TIFFWarningExt at tif_warning.c:63:6 in tiffio.h
// TIFFClientOpen at tif_open.c:289:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <tiffio.h>

static size_t custom_read(thandle_t handle, void *buf, size_t size) {
    FILE *f = (FILE *)handle;
    return fread(buf, 1, size, f);
}

static size_t custom_write(thandle_t handle, const void *buf, size_t size) {
    FILE *f = (FILE *)handle;
    return fwrite(buf, 1, size, f);
}

static toff_t custom_seek(thandle_t handle, toff_t offset, int whence) {
    FILE *f = (FILE *)handle;
    fseek(f, offset, whence);
    return ftell(f);
}

static void custom_close(thandle_t handle) {
    FILE *f = (FILE *)handle;
    fclose(f);
}

static toff_t custom_size(thandle_t handle) {
    FILE *f = (FILE *)handle;
    long current = ftell(f);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, current, SEEK_SET);
    return size;
}

int LLVMFuzzerTestOneInput_122(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file to work with
    FILE *dummy_file = fopen("./dummy_file", "wb+");
    if (!dummy_file) return 0;

    // Write the fuzz data to the dummy file
    fwrite(Data, 1, Size, dummy_file);
    fflush(dummy_file);
    rewind(dummy_file);

    // Test TIFFClientOpen
    TIFF *tiff_handle = TIFFClientOpen("dummy_file", "r", (thandle_t)dummy_file,
                                        (TIFFReadWriteProc)custom_read, 
                                        (TIFFReadWriteProc)custom_write,
                                        (TIFFSeekProc)custom_seek, 
                                        (TIFFCloseProc)custom_close,
                                        (TIFFSizeProc)custom_size, 
                                        NULL, NULL);
    if (tiff_handle) {
        // Test TIFFWarningExt
        TIFFWarningExt((thandle_t)tiff_handle, "Fuzzer", "Testing TIFFWarningExt");
        
        // Test TIFFErrorExt
        TIFFErrorExt((thandle_t)tiff_handle, "Fuzzer", "Testing TIFFErrorExt");

        // Close the TIFF handle
        TIFFClose(tiff_handle);
    }

    // Clean up
    fclose(dummy_file);
    return 0;
}