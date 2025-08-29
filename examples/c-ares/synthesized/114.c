// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_init_options at ares_init.c:238:5 in ares.h
// ares_set_servers at ares_update_servers.c:1221:5 in ares.h
// ares_set_sortlist at ares_init.c:576:5 in ares.h
// ares_set_servers_ports_csv at ares_update_servers.c:1309:5 in ares.h
// ares_version at ares_version.c:29:13 in ares.h
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

int LLVMFuzzerTestOneInput_114(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    ares_channel_t *channel;
    struct ares_options options;
    int optmask = 0;
    int status = ares_init_options(&channel, &options, optmask);
    if (status != ARES_SUCCESS) {
        return 0;
    }

    // Fuzz ares_set_servers
    struct ares_addr_node servers;
    servers.next = NULL;
    servers.family = AF_INET;
    servers.addr.addr4.s_addr = htonl(0x7F000001); // 127.0.0.1
    ares_set_servers(channel, &servers);

    // Fuzz ares_set_sortlist
    char *sortstr = (char *)malloc(Size + 1);
    if (sortstr) {
        memcpy(sortstr, Data, Size);
        sortstr[Size] = '\0';
        ares_set_sortlist(channel, sortstr);
        free(sortstr);
    }

    // Fuzz ares_set_servers_ports_csv
    char *csv = (char *)malloc(Size + 1);
    if (csv) {
        memcpy(csv, Data, Size);
        csv[Size] = '\0';
        ares_set_servers_ports_csv(channel, csv);
        free(csv);
    }

    // Fuzz ares_version
    int version;
    const char *ver_str = ares_version(&version);

    // Cleanup
    ares_destroy(channel);

    return 0;
}