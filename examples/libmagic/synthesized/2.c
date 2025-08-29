// This fuzz driver is generated for library libmagic, aiming to fuzz the following functions:
// magic_open at magic.c:267:1 in magic.h
// magic_errno at magic.c:575:1 in magic.h
// magic_load at magic.c:317:1 in magic.h
// magic_open at magic.c:267:1 in magic.h
// magic_list at magic.c:356:1 in magic.h
// magic_close at magic.c:306:1 in magic.h
// magic_open at magic.c:267:1 in magic.h
// magic_check at magic.c:348:1 in magic.h
// magic_close at magic.c:306:1 in magic.h
// magic_close at magic.c:306:1 in magic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <magic.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file with the fuzzed data
    int fd = open("./dummy_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) return 0;
    write(fd, Data, Size);
    close(fd);

    // Test magic_open
    magic_t magic_cookie = magic_open(MAGIC_NONE);
    if (magic_cookie == NULL) return 0;

    // Test magic_errno
    int err = magic_errno(magic_cookie);

    // Test magic_load
    magic_load(magic_cookie, NULL);

    // Test magic_list
    magic_t magic_cookie_list = magic_open(MAGIC_NONE);
    if (magic_cookie_list != NULL) {
        magic_list(magic_cookie_list, "./dummy_file");
        magic_close(magic_cookie_list);
    }

    // Test magic_check
    magic_t magic_cookie_check = magic_open(MAGIC_NONE);
    if (magic_cookie_check != NULL) {
        magic_check(magic_cookie_check, "./dummy_file");
        magic_close(magic_cookie_check);
    }

    // Clean up
    magic_close(magic_cookie);
    unlink("./dummy_file");

    return 0;
}