// This fuzz driver is generated for library libmagic, aiming to fuzz the following functions:
// magic_getpath at magic.c:254:1 in magic.h
// magic_version at magic.c:605:1 in magic.h
// magic_version at magic.c:605:1 in magic.h
// magic_open at magic.c:267:1 in magic.h
// magic_close at magic.c:306:1 in magic.h
// magic_check at magic.c:348:1 in magic.h
// magic_compile at magic.c:340:1 in magic.h
// magic_open at magic.c:267:1 in magic.h
// magic_list at magic.c:356:1 in magic.h
// magic_close at magic.c:306:1 in magic.h
// magic_error at magic.c:567:1 in magic.h
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

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    const char *magic_path = magic_getpath(NULL, 0);
    int version = magic_version();
    version = magic_version();

    magic_t magic_cookie = magic_open(MAGIC_NONE);
    if (magic_cookie == NULL) {
        return 0;
    }

    int fd = open("./dummy_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        magic_close(magic_cookie);
        return 0;
    }
    write(fd, Data, Size);
    close(fd);

    magic_check(magic_cookie, "./dummy_file");
    magic_compile(magic_cookie, "./dummy_file");

    magic_t magic_cookie_list = magic_open(MAGIC_NONE);
    if (magic_cookie_list != NULL) {
        magic_list(magic_cookie_list, "./dummy_file");
        magic_close(magic_cookie_list);
    }

    const char *error = magic_error(magic_cookie);
    magic_close(magic_cookie);

    unlink("./dummy_file");

    return 0;
}