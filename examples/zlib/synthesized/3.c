// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:263:16 in zlib.h
// gztell at gzlib.c:438:17 in zlib.h
// gzgetc at gzread.c:409:13 in zlib.h
// gzungetc at gzread.c:439:13 in zlib.h
// gzgets at gzread.c:500:16 in zlib.h
// gzerror at gzlib.c:490:22 in zlib.h
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

int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    // Write the input data to a dummy file
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

    // Call gztell
    z_off_t pos = gztell(file);

    // Call gzgetc
    int c = gzgetc(file);

    // Call gzungetc if gzgetc didn't return -1
    if (c != -1) {
        gzungetc(c, file);
    }

    // Call gzgets
    char buf[1024];
    gzgets(file, buf, sizeof(buf));

    // Call gzerror
    int errnum;
    const char *errmsg = gzerror(file, &errnum);

    // Call gzclose
    gzclose(file);

    // Clean up the dummy file
    remove("./dummy_file");

    return 0;
}