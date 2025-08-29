// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen64 at gzlib.c:268:16 in zlib.h
// gztell at gzlib.c:438:17 in zlib.h
// gzgets at gzread.c:500:16 in zlib.h
// gzseek at gzlib.c:415:17 in zlib.h
// gzopen64 at gzlib.c:268:16 in zlib.h
// gzprintf at gzwrite.c:430:15 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzdopen at gzlib.c:273:16 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <zlib.h>

#define DUMMY_FILE "./dummy_file"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there is at least some data

    // Write data to a dummy file
    write_dummy_file(Data, Size);

    // Open the gzipped file using gzopen64
    gzFile gz = gzopen64(DUMMY_FILE, "rb");
    if (gz == NULL) return 0;

    // Use gztell to get the current position
    z_off_t pos = gztell(gz);

    // Prepare a buffer for gzgets
    char buffer[256];
    gzgets(gz, buffer, sizeof(buffer));

    // Use gzseek to change the position
    gzseek(gz, pos, SEEK_SET);

    // Use gzprintf to write to a gzipped file
    gzFile write_gz = gzopen64(DUMMY_FILE, "wb");
    if (write_gz != NULL) {
        gzprintf(write_gz, "Test data: %.*s", (int)Size, Data);
        gzclose(write_gz);
    }

    // Close the gzipped file
    gzclose(gz);

    // Use gzdopen to open a file descriptor
    int fd = open(DUMMY_FILE, O_RDONLY);
    if (fd != -1) {
        gzFile fd_gz = gzdopen(fd, "rb");
        if (fd_gz != NULL) {
            gzclose(fd_gz);
        } else {
            close(fd);
        }
    }

    return 0;
}