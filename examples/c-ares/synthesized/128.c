// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_init_options at ares_init.c:238:5 in ares.h
// ares_set_servers_ports at ares_update_servers.c:1245:5 in ares.h
// ares_set_sortlist at ares_init.c:576:5 in ares.h
// ares_get_servers_ports at ares_update_servers.c:1164:5 in ares.h
// ares_free_data at ares_data.c:46:6 in ares.h
// ares_set_servers_csv at ares_update_servers.c:1304:5 in ares.h
// ares_destroy at ares_destroy.c:32:6 in ares.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_128(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    ares_channel_t *channel;
    struct ares_options options;
    int optmask = 0;

    if (ares_init_options(&channel, &options, optmask) != ARES_SUCCESS) {
        return 0;
    }

    // Fuzz ares_set_servers_ports
    struct ares_addr_port_node servers;
    servers.next = NULL;
    servers.family = AF_INET;
    servers.addr.addr4.s_addr = 0x01020304;
    servers.udp_port = 53;
    servers.tcp_port = 53;
    ares_set_servers_ports(channel, &servers);

    // Fuzz ares_set_sortlist
    char *sortstr = (char *)malloc(Size + 1);
    if (sortstr) {
        memcpy(sortstr, Data, Size);
        sortstr[Size] = '\0';
        ares_set_sortlist(channel, sortstr);
        free(sortstr);
    }

    // Fuzz ares_get_servers_ports
    struct ares_addr_port_node *servers_list;
    ares_get_servers_ports(channel, &servers_list);
    if (servers_list) {
        ares_free_data(servers_list);
    }

    // Fuzz ares_set_servers_csv
    char *csv_servers = (char *)malloc(Size + 1);
    if (csv_servers) {
        memcpy(csv_servers, Data, Size);
        csv_servers[Size] = '\0';
        ares_set_servers_csv(channel, csv_servers);
        free(csv_servers);
    }

    ares_destroy(channel);
    return 0;
}