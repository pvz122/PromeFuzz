// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFGetReadProc at tif_open.c:912:19 in tiffio.h
// TIFFGetWriteProc at tif_open.c:917:19 in tiffio.h
// TIFFGetCloseProc at tif_open.c:927:15 in tiffio.h
// TIFFGetSizeProc at tif_open.c:932:14 in tiffio.h
// TIFFGetMapFileProc at tif_open.c:937:17 in tiffio.h
// TIFFClientOpen at tif_open.c:289:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <tiffio.h>

long dummy_read(thandle_t handle, void *buf, long size) { return size; }
long dummy_write(thandle_t handle, void *buf, long size) { return size; }
toff_t dummy_seek(thandle_t handle, toff_t offset, int whence) { return offset; }
int dummy_close(thandle_t handle) { return 0; }
toff_t dummy_size(thandle_t handle) { return 0; }
int dummy_map(thandle_t handle, void **base, toff_t *size) { return 0; }
void dummy_unmap(thandle_t handle, void *base, toff_t size) {}

int LLVMFuzzerTestOneInput_125(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    const char *filename = "./dummy_file";
    FILE *file = fopen(filename, "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    thandle_t handle = NULL;
    TIFF *tiff = TIFFClientOpen(filename, "r", handle,
                                 dummy_read, dummy_write,
                                 dummy_seek, dummy_close,
                                 dummy_size, dummy_map, dummy_unmap);
    
    if (tiff) {
        TIFFCloseProc closeProc = TIFFGetCloseProc(tiff);
        TIFFMapFileProc mapProc = TIFFGetMapFileProc(tiff);
        TIFFReadWriteProc writeProc = TIFFGetWriteProc(tiff);
        TIFFReadWriteProc readProc = TIFFGetReadProc(tiff);
        TIFFSizeProc sizeProc = TIFFGetSizeProc(tiff);

        // Explore different states by invoking various procedures
        if (closeProc) closeProc(handle);
        if (mapProc) mapProc(handle, NULL, NULL);
        if (writeProc) writeProc(handle, NULL, 0);
        if (readProc) readProc(handle, NULL, 0);
        if (sizeProc) sizeProc(handle);

        // Cleanup
        TIFFClose(tiff);
    }

    return 0;
}