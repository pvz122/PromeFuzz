// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:263:16 in zlib.h
// gzseek at gzlib.c:415:17 in zlib.h
// gzopen at gzlib.c:263:16 in zlib.h
// gzflush at gzwrite.c:528:13 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzrewind at gzlib.c:321:13 in zlib.h
// gzclearerr at gzlib.c:508:14 in zlib.h
// gzclose_r at gzread.c:578:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file with the fuzzed data
    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) return 0;
    fwrite(Data, 1, Size, fp);
    fclose(fp);

    // Open the dummy file with zlib
    gzFile file = gzopen("./dummy_file", "rb");
    if (!file) {
        remove("./dummy_file");
        return 0;
    }

    // Fuzz gzseek
    int whence = Data[0] % 2 == 0 ? SEEK_SET : SEEK_CUR;
    z_off_t offset = (z_off_t)Data[0];
    gzseek(file, offset, whence);

    // Fuzz gzflush (only valid in write mode, so open in write mode)
    gzFile writeFile = gzopen("./dummy_file", "wb");
    if (writeFile) {
        gzflush(writeFile, Z_SYNC_FLUSH);
        gzclose(writeFile);
    }

    // Fuzz gzrewind
    gzrewind(file);

    // Fuzz gzclearerr
    gzclearerr(file);

    // Clean up
    gzclose_r(file);
    remove("./dummy_file");

    return 0;
}