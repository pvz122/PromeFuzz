// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFCleanup at tif_close.c:44:6 in tiffio.h
// TIFFGetReadProc at tif_open.c:912:19 in tiffio.h
// TIFFGetWriteProc at tif_open.c:917:19 in tiffio.h
// TIFFGetCloseProc at tif_open.c:927:15 in tiffio.h
// TIFFGetSizeProc at tif_open.c:932:14 in tiffio.h
// TIFFClientOpen at tif_open.c:289:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <tiffio.h>

static size_t custom_read(thandle_t handle, void *buffer, size_t size) {
    return fread(buffer, 1, size, (FILE *)handle);
}

static size_t custom_write(thandle_t handle, void *buffer, size_t size) {
    return fwrite(buffer, 1, size, (FILE *)handle);
}

static toff_t custom_seek(thandle_t handle, toff_t offset, int whence) {
    return (toff_t)fseek((FILE *)handle, (long)offset, whence);
}

static void custom_close(thandle_t handle) {
    fclose((FILE *)handle);
}

static toff_t custom_size(thandle_t handle) {
    long current_pos = ftell((FILE *)handle);
    fseek((FILE *)handle, 0, SEEK_END);
    long size = ftell((FILE *)handle);
    fseek((FILE *)handle, current_pos, SEEK_SET);
    return (toff_t)size;
}

int LLVMFuzzerTestOneInput_137(const uint8_t *Data, size_t Size) {
    // Create a dummy file
    FILE *dummy_file = fopen("./dummy_file", "wb+");
    if (!dummy_file) return 0;

    // Write the fuzz data to the dummy file
    fwrite(Data, 1, Size, dummy_file);
    fflush(dummy_file);
    
    // Reset file position for reading
    rewind(dummy_file);

    // Open the TIFF file using custom handlers
    TIFF *tif = TIFFClientOpen("./dummy_file", "r", (thandle_t)dummy_file,
                                (TIFFReadWriteProc)custom_read, 
                                (TIFFReadWriteProc)custom_write,
                                (TIFFSeekProc)custom_seek, 
                                (TIFFCloseProc)custom_close,
                                (TIFFSizeProc)custom_size, NULL, NULL);
    
    if (tif) {
        // Retrieve various procedures
        TIFFCloseProc close_proc = TIFFGetCloseProc(tif);
        TIFFReadWriteProc write_proc = TIFFGetWriteProc(tif);
        TIFFReadWriteProc read_proc = TIFFGetReadProc(tif);
        TIFFSizeProc size_proc = TIFFGetSizeProc(tif);

        // Invoke the procedures to explore states
        if (close_proc) close_proc(tif);
        if (write_proc) write_proc(tif, Data, Size);
        if (read_proc) read_proc(tif, Data, Size);
        if (size_proc) size_proc(tif);

        // Cleanup the TIFF structure
        TIFFCleanup(tif);
    }

    // Close the dummy file
    fclose(dummy_file);
    return 0;
}