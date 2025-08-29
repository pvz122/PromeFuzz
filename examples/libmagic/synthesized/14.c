// This fuzz driver is generated for library libmagic, aiming to fuzz the following functions:
// magic_open at magic.c:267:1 in magic.h
// magic_descriptor at magic.c:402:1 in magic.h
// magic_getflags at magic.c:583:1 in magic.h
// magic_setflags at magic.c:592:1 in magic.h
// magic_load_buffers at magic.c:329:1 in magic.h
// magic_buffer at magic.c:549:1 in magic.h
// magic_getparam at magic.c:654:1 in magic.h
// magic_close at magic.c:306:1 in magic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <magic.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    magic_t magic_cookie = magic_open(MAGIC_NONE);
    if (magic_cookie == NULL) {
        return 0;
    }

    // Test magic_descriptor
    int fd = open("./dummy_file", O_RDWR | O_CREAT, 0644);
    if (fd != -1) {
        write(fd, Data, Size);
        lseek(fd, 0, SEEK_SET);
        magic_descriptor(magic_cookie, fd);
        close(fd);
    }

    // Test magic_getflags
    magic_getflags(magic_cookie);

    // Test magic_setflags
    magic_setflags(magic_cookie, MAGIC_NONE);

    // Test magic_load_buffers
    void *buffers[] = {(void *)Data};
    size_t sizes[] = {Size};
    magic_load_buffers(magic_cookie, buffers, sizes, 1);

    // Test magic_buffer
    magic_buffer(magic_cookie, Data, Size);

    // Test magic_getparam
    size_t param_value;
    magic_getparam(magic_cookie, MAGIC_PARAM_INDIR_MAX, &param_value);

    magic_close(magic_cookie);
    return 0;
}