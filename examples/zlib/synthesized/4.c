// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:263:16 in zlib.h
// gzerror at gzlib.c:490:22 in zlib.h
// gzprintf at gzwrite.c:430:15 in zlib.h
// gzerror at gzlib.c:490:22 in zlib.h
// gzseek at gzlib.c:415:17 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file with the given data
    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) return 0;
    fwrite(Data, 1, Size, fp);
    fclose(fp);

    // Open the dummy file with gzopen
    gzFile file = gzopen("./dummy_file", "rb");
    if (!file) {
        remove("./dummy_file");
        return 0;
    }

    int errnum;
    const char *error_msg;

    // First call to gzerror
    error_msg = gzerror(file, &errnum);

    // Call to gzprintf
    gzprintf(file, "Test format %d", 123);

    // Second call to gzerror
    error_msg = gzerror(file, &errnum);

    // Call to gzseek
    z_off_t result = gzseek(file, 0, SEEK_SET);

    // Clean up
    gzclose(file);
    remove("./dummy_file");

    return 0;
}