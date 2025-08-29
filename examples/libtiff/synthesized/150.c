// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFSetClientdata at tif_open.c:833:11 in tiffio.h
// TIFFFileName at tif_open.c:798:13 in tiffio.h
// TIFFSetFileName at tif_open.c:803:13 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
// TIFFFdOpen at tif_unix.c:205:7 in tiffio.h
// TIFFClientOpen at tif_open.c:289:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_150(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Create a dummy file for testing
    const char *filename = "./dummy_file";
    FILE *file = fopen(filename, "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Test TIFFOpen
    TIFF *tif = TIFFOpen(filename, "rh");
    if (tif) {
        // Test TIFFSetClientdata
        thandle_t client_data = (thandle_t)malloc(16);
        TIFFSetClientdata(tif, client_data);

        // Test TIFFFileName
        const char *file_name = TIFFFileName(tif);

        // Test TIFFSetFileName
        const char *old_file_name = TIFFSetFileName(tif, "new_dummy_file");

        // Cleanup
        free(client_data);
        TIFFClose(tif);
    }

    // Test TIFFClientOpen
    TIFF *tif_custom = TIFFClientOpen("dummy", "r", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    if (tif_custom) {
        // Test TIFFSetClientdata
        thandle_t custom_client_data = (thandle_t)malloc(32);
        TIFFSetClientdata(tif_custom, custom_client_data);

        // Test TIFFFileName
        const char *custom_file_name = TIFFFileName(tif_custom);

        // Cleanup
        free(custom_client_data);
        TIFFClose(tif_custom);
    }

    // Test TIFFFdOpen
    int fd = open(filename, O_RDONLY);
    if (fd != -1) {
        TIFF *tif_fd = TIFFFdOpen(fd, filename, "r");
        if (tif_fd) {
            // Test TIFFSetClientdata
            thandle_t fd_client_data = (thandle_t)malloc(64);
            TIFFSetClientdata(tif_fd, fd_client_data);

            // Cleanup
            free(fd_client_data);
            TIFFClose(tif_fd);
        }
        close(fd);
    }

    // Remove the dummy file
    remove(filename);

    return 0;
}