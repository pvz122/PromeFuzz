// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_library_init at ares_library_init.c:108:5 in ares.h
// ares_strerror at ares_strerror.c:30:13 in ares.h
// ares_init_options at ares_init.c:238:5 in ares.h
// ares_strerror at ares_strerror.c:30:13 in ares.h
// ares_get_servers_csv at ares_update_servers.c:1314:7 in ares.h
// ares_free_string at ares_free_string.c:30:6 in ares.h
// ares_destroy at ares_destroy.c:32:6 in ares.h
// ares_library_cleanup at ares_library_init.c:139:6 in ares.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(int)) {
        return 0;
    }

    int flags = *(int *)Data;
    ares_library_init(flags);

    int error_code = *(int *)(Data + sizeof(int));
    const char *error_str = ares_strerror(error_code);

    ares_channel_t *channel = NULL;
    struct ares_options options;
    memset(&options, 0, sizeof(options));
    int optmask = 0;

    int init_result = ares_init_options(&channel, &options, optmask);
    if (init_result == ARES_SUCCESS) {
        const char *error_str2 = ares_strerror(init_result);
        char *servers_csv = ares_get_servers_csv(channel);
        if (servers_csv) {
            ares_free_string(servers_csv);
        }
        ares_destroy(channel);
    }

    ares_library_cleanup();
    return 0;
}