// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_init at ares_init.c:67:5 in ares.h
// ares_expand_string at ares_expand_string.c:93:5 in ares.h
// ares_fds at ares_fds.c:30:5 in ares.h
// ares_getaddrinfo at ares_getaddrinfo.c:686:6 in ares.h
// ares_destroy at ares_destroy.c:32:6 in ares.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void dummy_callback(void *arg, int status, int timeouts, struct ares_addrinfo *result) {
    // Do nothing
}

int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    ares_channel *channel;
    if (ares_init(&channel) != ARES_SUCCESS) {
        return 0;
    }

    unsigned char *s = NULL;
    long enclen = 0;
    int ret = ares_expand_string(Data, Data, Size, &s, &enclen);
    if (ret == ARES_SUCCESS) {
        free(s);
    }

    fd_set read_fds, write_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    ares_fds(channel, &read_fds, &write_fds);

    struct ares_addrinfo_hints hints;
    memset(&hints, 0, sizeof(hints));
    ares_getaddrinfo(channel, "example.com", NULL, &hints, dummy_callback, NULL);

    ares_destroy(channel);
    return 0;
}