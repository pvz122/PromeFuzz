// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFSetClientdata at tif_open.c:833:11 in tiffio.h
// TIFFGetSeekProc at tif_open.c:922:14 in tiffio.h
// TIFFGetMapFileProc at tif_open.c:937:17 in tiffio.h
// TIFFGetUnmapFileProc at tif_open.c:942:19 in tiffio.h
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

static size_t custom_write(thandle_t handle, void *buf, size_t size) {
    FILE *f = (FILE *)handle;
    return fwrite(buf, 1, size, f);
}

static int custom_seek(thandle_t handle, uint64_t offset, int whence) {
    FILE *f = (FILE *)handle;
    return fseek(f, offset, whence);
}

static void custom_close(thandle_t handle) {
    fclose((FILE *)handle);
}

static uint64_t custom_size(thandle_t handle) {
    FILE *f = (FILE *)handle;
    long current = ftell(f);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, current, SEEK_SET);
    return size;
}

int LLVMFuzzerTestOneInput_113(const uint8_t *Data, size_t Size) {
    // Prepare a dummy file to work with
    FILE *dummy_file = fopen("./dummy_file", "wb+");
    if (!dummy_file) return 0;

    // Write the fuzz data to the dummy file
    fwrite(Data, 1, Size, dummy_file);
    fflush(dummy_file);
    rewind(dummy_file);

    // Open the TIFF file using the custom handlers
    TIFF *tif = TIFFClientOpen("dummy_file", "r", (thandle_t)dummy_file,
                                (TIFFReadWriteProc)custom_read, 
                                (TIFFReadWriteProc)custom_write,
                                (TIFFSeekProc)custom_seek, 
                                (TIFFCloseProc)custom_close,
                                (TIFFSizeProc)custom_size, NULL, NULL);
    
    if (tif) {
        // Test various API functions
        TIFFMapFileProc mapProc = TIFFGetMapFileProc(tif);
        TIFFUnmapFileProc unmapProc = TIFFGetUnmapFileProc(tif);
        TIFFSeekProc seekProc = TIFFGetSeekProc(tif);

        // Set and get client data
        thandle_t clientData = (thandle_t)malloc(10);
        TIFFSetClientdata(tif, clientData);
        thandle_t prevData = TIFFSetClientdata(tif, NULL);
        free(prevData);

        // Clean up
        TIFFClose(tif);
    }

    // Cleanup the dummy file
    remove("./dummy_file");
    return 0;
}