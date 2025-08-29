// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:263:16 in zlib.h
// gztell at gzlib.c:438:17 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzseek at gzlib.c:415:17 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzgets at gzread.c:500:16 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzopen at gzlib.c:263:16 in zlib.h
// gzputs at gzwrite.c:332:13 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzprintf at gzwrite.c:430:15 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write data to a dummy file
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

    // Test gztell
    z_off_t pos = gztell(file);
    if (pos == -1) {
        gzclose(file);
        remove("./dummy_file");
        return 0;
    }

    // Test gzseek
    pos = gzseek(file, 0, SEEK_SET);
    if (pos == -1) {
        gzclose(file);
        remove("./dummy_file");
        return 0;
    }

    // Test gzgets
    char buf[1024];
    char *result = gzgets(file, buf, sizeof(buf));
    if (!result) {
        gzclose(file);
        remove("./dummy_file");
        return 0;
    }

    // Close the file and reopen in write mode
    gzclose(file);
    file = gzopen("./dummy_file", "wb");
    if (!file) {
        remove("./dummy_file");
        return 0;
    }

    // Test gzputs
    const char *str = "test string";
    int ret = gzputs(file, str);
    if (ret == -1) {
        gzclose(file);
        remove("./dummy_file");
        return 0;
    }

    // Test gzprintf
    ret = gzprintf(file, "Format: %s\n", str);
    if (ret < 0) {
        gzclose(file);
        remove("./dummy_file");
        return 0;
    }

    gzclose(file);
    remove("./dummy_file");
    return 0;
}