// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_init at ares_init.c:67:5 in ares.h
// ares_getnameinfo at ares_getnameinfo.c:188:6 in ares.h
// ares_query at ares_query.c:133:6 in ares.h
// ares_gethostbyaddr at ares_gethostbyaddr.c:108:6 in ares.h
// ares_dup at ares_init.c:454:5 in ares.h
// ares_threadsafety at ares_threads.c:632:13 in ares.h
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
#include <arpa/inet.h>

static void dummy_callback(void *arg, int status, int timeouts, unsigned char *abuf, int alen) {
    // Do nothing
}

static void dummy_nameinfo_callback(void *arg, int status, int timeouts, char *node, char *service) {
    // Do nothing
}

static void dummy_host_callback(void *arg, int status, int timeouts, struct hostent *hostent) {
    // Do nothing
}

int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    ares_channel_t *channel;
    ares_channel_t *dup_channel;
    struct sockaddr_in sa;
    char *name = malloc(Size + 1);
    if (!name) return 0;
    memcpy(name, Data, Size);
    name[Size] = '\0';
    int dnsclass = ARES_CLASS_IN;
    int type = 1; // T_A is 1 for A record
    void *addr = &sa.sin_addr;
    int addrlen = sizeof(sa.sin_addr);
    int family = AF_INET;
    int flags = 0;

    // Initialize channel
    if (ares_init(&channel) != ARES_SUCCESS) {
        free(name);
        return 0;
    }

    // Fuzz ares_getnameinfo
    ares_getnameinfo(channel, (const struct sockaddr *)&sa, sizeof(sa), flags, dummy_nameinfo_callback, NULL);

    // Fuzz ares_query
    ares_query(channel, name, dnsclass, type, dummy_callback, NULL);

    // Fuzz ares_gethostbyaddr
    ares_gethostbyaddr(channel, addr, addrlen, family, dummy_host_callback, NULL);

    // Fuzz ares_dup
    ares_dup(&dup_channel, channel);

    // Fuzz ares_threadsafety
    ares_threadsafety();

    // Cleanup
    if (dup_channel) {
        ares_destroy(dup_channel);
    }
    ares_destroy(channel);
    free(name);

    return 0;
}