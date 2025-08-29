// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_init_options at ares_init.c:238:5 in ares.h
// ares_set_servers_ports at ares_update_servers.c:1245:5 in ares.h
// ares_dup at ares_init.c:454:5 in ares.h
// ares_get_servers_csv at ares_update_servers.c:1314:7 in ares.h
// ares_free_string at ares_free_string.c:30:6 in ares.h
// ares_getsock at ares_getsock.c:29:5 in ares.h
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

int LLVMFuzzerTestOneInput_124(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct ares_addr_port_node)) {
        return 0;
    }

    ares_channel_t *channel = NULL;
    struct ares_options options;
    int optmask = 0;

    if (ares_init_options(&channel, &options, optmask) != ARES_SUCCESS) {
        return 0;
    }

    struct ares_addr_port_node servers;
    memcpy(&servers, Data, sizeof(struct ares_addr_port_node));
    servers.next = NULL; // Ensure the linked list is properly terminated

    ares_set_servers_ports(channel, &servers);

    ares_channel_t *dup_channel = NULL;
    ares_dup(&dup_channel, channel);

    char *csv = ares_get_servers_csv(channel);
    if (csv) {
        ares_free_string(csv);
    }

    ares_socket_t socks[ARES_GETSOCK_MAXNUM];
    ares_getsock(channel, socks, ARES_GETSOCK_MAXNUM);

    ares_destroy(channel);
    if (dup_channel) {
        ares_destroy(dup_channel);
    }

    return 0;
}