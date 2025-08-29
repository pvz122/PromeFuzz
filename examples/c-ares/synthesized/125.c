// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_init at ares_init.c:67:5 in ares.h
// ares_destroy at ares_destroy.c:32:6 in ares.h
// ares_query at ares_query.c:133:6 in ares.h
// ares_getnameinfo at ares_getnameinfo.c:188:6 in ares.h
// ares_gethostbyaddr at ares_gethostbyaddr.c:108:6 in ares.h
// ares_dup at ares_init.c:454:5 in ares.h
// ares_destroy at ares_destroy.c:32:6 in ares.h
// ares_search at ares_search.c:431:6 in ares.h
// ares_destroy at ares_destroy.c:32:6 in ares.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>

static void query_callback(void *arg, int status, int timeouts, unsigned char *abuf, int alen) {
    (void)arg;
    (void)status;
    (void)timeouts;
    (void)abuf;
    (void)alen;
}

static void nameinfo_callback(void *arg, int status, int timeouts, char *node, char *service) {
    (void)arg;
    (void)status;
    (void)timeouts;
    (void)node;
    (void)service;
}

static void host_callback(void *arg, int status, int timeouts, struct hostent *hostent) {
    (void)arg;
    (void)status;
    (void)timeouts;
    (void)hostent;
}

int LLVMFuzzerTestOneInput_125(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    ares_channel_t *channel;
    if (ares_init(&channel) != ARES_SUCCESS) {
        return 0;
    }

    char *name = (char *)malloc(Size + 1);
    if (!name) {
        ares_destroy(channel);
        return 0;
    }
    memcpy(name, Data, Size);
    name[Size] = '\0';

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(53);
    inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr);

    ares_query(channel, name, C_IN, T_A, query_callback, NULL);
    ares_getnameinfo(channel, (struct sockaddr *)&sa, sizeof(sa), 0, nameinfo_callback, NULL);
    ares_gethostbyaddr(channel, &sa.sin_addr, sizeof(sa.sin_addr), AF_INET, host_callback, NULL);

    ares_channel_t *dup_channel;
    ares_dup(&dup_channel, channel);
    if (dup_channel) {
        ares_destroy(dup_channel);
    }

    ares_search(channel, name, C_IN, T_A, query_callback, NULL);

    free(name);
    ares_destroy(channel);
    return 0;
}