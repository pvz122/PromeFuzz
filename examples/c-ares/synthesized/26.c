// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_init at ares_init.c:67:5 in ares.h
// ares_set_socket_functions at ares_set_socket_functions.c:577:6 in ares.h
// ares_destroy at ares_destroy.c:32:6 in ares.h
// ares_expand_name at ares_expand_name.c:84:5 in ares.h
// ares_free_string at ares_free_string.c:30:6 in ares.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static ares_socket_t dummy_socket(int domain, int type, int protocol, void *user_data) {
    return ARES_SOCKET_BAD;
}

static int dummy_close(ares_socket_t sock, void *user_data) {
    return 0;
}

static int dummy_connect(ares_socket_t sock, const struct sockaddr *addr, ares_socklen_t len, void *user_data) {
    return -1;
}

static ares_ssize_t dummy_recvfrom(ares_socket_t sock, void *buf, size_t len, int flags, struct sockaddr *addr, ares_socklen_t *addrlen, void *user_data) {
    return -1;
}

static ares_ssize_t dummy_sendv(ares_socket_t sock, const struct iovec *vec, int len, void *user_data) {
    return -1;
}

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    ares_channel_t *channel;
    if (ares_init(&channel) != ARES_SUCCESS) {
        return 0;
    }

    struct ares_socket_functions funcs = {
        .asocket = dummy_socket,
        .aclose = dummy_close,
        .aconnect = dummy_connect,
        .arecvfrom = dummy_recvfrom,
        .asendv = dummy_sendv
    };

    ares_set_socket_functions(channel, &funcs, NULL);

    ares_destroy(channel);

    char *output = NULL;
    long enclen;
    unsigned char *encoded = (unsigned char *)data;
    int alen = size;
    ares_expand_name(encoded, encoded, alen, &output, &enclen);

    if (output) {
        ares_free_string(output);
    }

    return 0;
}