// This fuzz driver is generated for library libmagic, aiming to fuzz the following functions:
// magic_open at magic.c:267:1 in magic.h
// magic_compile at magic.c:340:1 in magic.h
// magic_descriptor at magic.c:402:1 in magic.h
// magic_open at magic.c:267:1 in magic.h
// magic_list at magic.c:356:1 in magic.h
// magic_close at magic.c:306:1 in magic.h
// magic_file at magic.c:413:1 in magic.h
// magic_error at magic.c:567:1 in magic.h
// magic_close at magic.c:306:1 in magic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <magic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file with the fuzzed data
    int fd = open("./dummy_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) return 0;
    write(fd, Data, Size);
    close(fd);

    // Initialize magic_set
    magic_t magic = magic_open(MAGIC_NONE);
    if (magic == NULL) return 0;

    // Fuzz magic_compile
    magic_compile(magic, "./dummy_file");

    // Fuzz magic_descriptor
    fd = open("./dummy_file", O_RDONLY);
    if (fd >= 0) {
        magic_descriptor(magic, fd);
        close(fd);
    }

    // Fuzz magic_list
    magic_t magic_list_set = magic_open(MAGIC_NONE);
    if (magic_list_set != NULL) {
        magic_list(magic_list_set, "./dummy_file");
        magic_close(magic_list_set);
    }

    // Fuzz magic_file
    magic_file(magic, "./dummy_file");

    // Fuzz magic_error
    magic_error(magic);

    // Clean up
    magic_close(magic);
    unlink("./dummy_file");

    return 0;
}