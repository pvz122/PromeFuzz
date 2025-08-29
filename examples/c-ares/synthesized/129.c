// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_init_options at ares_init.c:238:5 in ares.h
// ares_set_socket_configure_callback at ares_socket.c:406:6 in ares.h
// ares_process at ares_process.c:329:6 in ares.h
// ares_search at ares_search.c:431:6 in ares.h
// ares_set_sortlist at ares_init.c:576:5 in ares.h
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
#include <arpa/nameser.h>

static int dummy_sock_config_callback(ares_socket_t socket_fd, int type, void *user_data) {
    return 0;
}

static void dummy_callback(void *arg, int status, int timeouts, unsigned char *abuf, int alen) {
    // Do nothing
}

int LLVMFuzzerTestOneInput_129(const uint8_t *Data, size_t Size) {
    ares_channel_t *channel;
    struct ares_options options;
    int optmask = 0;

    // Initialize channel
    if (ares_init_options(&channel, &options, optmask) != ARES_SUCCESS) {
        return 0;
    }

    // Fuzz ares_set_socket_configure_callback
    ares_set_socket_configure_callback(channel, dummy_sock_config_callback, NULL);

    // Fuzz ares_process
    fd_set read_fds, write_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    ares_process(channel, &read_fds, &write_fds);

    // Fuzz ares_search
    if (Size > 0) {
        char *name = (char *)malloc(Size + 1);
        if (name) {
            memcpy(name, Data, Size);
            name[Size] = '\0';
            ares_search(channel, name, ns_c_in, ns_t_a, dummy_callback, NULL);
            free(name);
        }
    }

    // Fuzz ares_set_sortlist
    if (Size > 0) {
        char *sortstr = (char *)malloc(Size + 1);
        if (sortstr) {
            memcpy(sortstr, Data, Size);
            sortstr[Size] = '\0';
            ares_set_sortlist(channel, sortstr);
            free(sortstr);
        }
    }

    // Cleanup
    ares_destroy(channel);

    return 0;
}