// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_init at ares_init.c:67:5 in ares.h
// ares_destroy at ares_destroy.c:32:6 in ares.h
// ares_set_socket_configure_callback at ares_socket.c:406:6 in ares.h
// ares_set_socket_functions at ares_set_socket_functions.c:577:6 in ares.h
// ares_set_socket_callback at ares_socket.c:396:6 in ares.h
// ares_process at ares_process.c:329:6 in ares.h
// ares_set_local_ip4 at ares_init.c:541:6 in ares.h
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

static ares_socket_t dummy_socket(int domain, int type, int protocol, void *user_data) {
    return ARES_SOCKET_BAD;
}

static int dummy_close(ares_socket_t sock, void *user_data) {
    return 0;
}

static int dummy_connect(ares_socket_t sock, const struct sockaddr *addr, ares_socklen_t len, void *user_data) {
    return -1;
}

static ares_ssize_t dummy_recvfrom(ares_socket_t sock, void *buffer, size_t length, int flags, struct sockaddr *addr, ares_socklen_t *addr_len, void *user_data) {
    return -1;
}

static ares_ssize_t dummy_sendv(ares_socket_t sock, const struct iovec *iov, int iov_count, void *user_data) {
    return -1;
}

static const struct ares_socket_functions dummy_socket_functions = {
    dummy_socket,
    dummy_close,
    dummy_connect,
    dummy_recvfrom,
    dummy_sendv
};

static int dummy_sock_config_callback(ares_socket_t socket_fd, int type, void *user_data) {
    return 0;
}

static ares_socket_t dummy_sock_create_callback(int af, int type, void *user_data) {
    return ARES_SOCKET_BAD;
}

int LLVMFuzzerTestOneInput_131(const uint8_t *Data, size_t Size) {
    ares_channel_t *channel;
    if (ares_init(&channel) != ARES_SUCCESS) {
        return 0;
    }

    if (Size < 1) {
        ares_destroy(channel);
        return 0;
    }

    uint8_t flags = Data[0];
    ares_set_socket_configure_callback(channel, dummy_sock_config_callback, NULL);
    ares_set_socket_functions(channel, &dummy_socket_functions, NULL);
    ares_set_socket_callback(channel, dummy_sock_create_callback, NULL);

    fd_set read_fds, write_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    ares_process(channel, &read_fds, &write_fds);

    unsigned int local_ip = 0;
    if (Size >= 5) {
        local_ip = *(unsigned int *)(Data + 1);
    }
    ares_set_local_ip4(channel, local_ip);

    ares_destroy(channel);
    return 0;
}