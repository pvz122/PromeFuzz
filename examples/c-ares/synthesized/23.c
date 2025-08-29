// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_init at ares_init.c:67:5 in ares.h
// ares_gethostbyname_file at ares_gethostbyname.c:335:5 in ares.h
// ares_gethostbyname_file at ares_gethostbyname.c:335:5 in ares.h
// ares_gethostbyname_file at ares_gethostbyname.c:335:5 in ares.h
// ares_free_hostent at ares_free_hostent.c:33:6 in ares.h
// ares_destroy at ares_destroy.c:32:6 in ares.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    ares_channel_t *channel = NULL;
    struct hostent *host = NULL;
    int family = (Data[0] % 2) ? AF_INET : AF_INET6;
    char name[256];

    if (Size > 256) {
        Size = 256;
    }
    memcpy(name, Data, Size);
    name[Size] = '\0';

    ares_init(&channel);
    ares_gethostbyname_file(channel, name, family, &host);
    ares_gethostbyname_file(channel, name, family, &host);
    ares_gethostbyname_file(channel, name, family, &host);

    if (host) {
        ares_free_hostent(host);
    }

    if (channel) {
        ares_destroy(channel);
    }

    return 0;
}