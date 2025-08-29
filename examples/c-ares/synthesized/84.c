// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_init_options at ares_init.c:238:5 in ares.h
// ares_dup at ares_init.c:454:5 in ares.h
// ares_destroy at ares_destroy.c:32:6 in ares.h
// ares_save_options at ares_options.c:83:5 in ares.h
// ares_destroy_options at ares_options.c:37:6 in ares.h
// ares_set_servers_csv at ares_update_servers.c:1304:5 in ares.h
// ares_init_options at ares_init.c:238:5 in ares.h
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

int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    ares_channel_t *channel = NULL;
    ares_channel_t *dup_channel = NULL;
    struct ares_options options;
    int optmask = 0;
    char *servers_csv = NULL;
    int ret;

    // Initialize channel
    ret = ares_init_options(&channel, NULL, 0);
    if (ret != ARES_SUCCESS) return 0;

    // Fuzz ares_dup
    ret = ares_dup(&dup_channel, channel);
    if (ret == ARES_SUCCESS && dup_channel != NULL) {
        ares_destroy(dup_channel);
    }

    // Fuzz ares_save_options
    ret = ares_save_options(channel, &options, &optmask);
    if (ret == ARES_SUCCESS) {
        ares_destroy_options(&options);
    }

    // Fuzz ares_set_servers_csv
    servers_csv = (char *)malloc(Size + 1);
    if (servers_csv) {
        memcpy(servers_csv, Data, Size);
        servers_csv[Size] = '\0';
        ret = ares_set_servers_csv(channel, servers_csv);
        free(servers_csv);
    }

    // Fuzz ares_init_options
    ret = ares_init_options(&dup_channel, &options, optmask);
    if (ret == ARES_SUCCESS && dup_channel != NULL) {
        ares_destroy(dup_channel);
    }

    ares_destroy(channel);
    return 0;
}