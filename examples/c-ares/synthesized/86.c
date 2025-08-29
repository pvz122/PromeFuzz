// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_init at ares_init.c:67:5 in ares.h
// ares_destroy at ares_destroy.c:32:6 in ares.h
// ares_query at ares_query.c:133:6 in ares.h
// ares_getnameinfo at ares_getnameinfo.c:188:6 in ares.h
// ares_gethostbyaddr at ares_gethostbyaddr.c:108:6 in ares.h
// ares_getaddrinfo at ares_getaddrinfo.c:686:6 in ares.h
// ares_dup at ares_init.c:454:5 in ares.h
// ares_destroy at ares_destroy.c:32:6 in ares.h
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

static void query_callback(void *arg, int status, int timeouts, unsigned char *abuf, int alen) {
    // Do nothing
}

static void nameinfo_callback(void *arg, int status, int timeouts, char *node, char *service) {
    // Do nothing
}

static void host_callback(void *arg, int status, int timeouts, struct hostent *hostent) {
    // Do nothing
}

static void addrinfo_callback(void *arg, int status, int timeouts, struct ares_addrinfo *res) {
    // Do nothing
}

int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0;

    ares_channel_t *channel;
    if (ares_init(&channel) != ARES_SUCCESS) {
        return 0;
    }

    // Fuzz ares_query
    char *name = malloc(Size + 1);
    if (!name) {
        ares_destroy(channel);
        return 0;
    }
    memcpy(name, Data, Size);
    name[Size] = '\0';
    int dnsclass = Data[0] % 256;
    int type = Data[1] % 256;
    ares_query(channel, name, dnsclass, type, query_callback, NULL);
    free(name);

    // Fuzz ares_getnameinfo
    struct sockaddr sa;
    memset(&sa, 0, sizeof(sa));
    ares_socklen_t salen = sizeof(sa);
    int flags = Data[2] % 256;
    ares_getnameinfo(channel, &sa, salen, flags, nameinfo_callback, NULL);

    // Fuzz ares_gethostbyaddr
    int addrlen = Size < 4 ? Size : 4;
    int family = Data[3] % 256;
    ares_gethostbyaddr(channel, Data, addrlen, family, host_callback, NULL);

    // Fuzz ares_getaddrinfo
    struct ares_addrinfo_hints hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = family;
    hints.ai_socktype = Data[4] % 256;
    hints.ai_protocol = Data[5] % 256;
    ares_getaddrinfo(channel, "example.com", NULL, &hints, addrinfo_callback, NULL);

    // Fuzz ares_dup
    ares_channel_t *dest;
    ares_dup(&dest, channel);

    ares_destroy(channel);
    if (dest) {
        ares_destroy(dest);
    }

    return 0;
}