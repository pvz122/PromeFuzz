// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_init at ares_init.c:67:5 in ares.h
// ares_queue_active_queries at ares_send.c:285:8 in ares.h
// ares_cancel at ares_cancel.c:34:6 in ares.h
// ares_destroy at ares_destroy.c:32:6 in ares.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    ares_channel_t *channel;
    if (ares_init(&channel) != ARES_SUCCESS) {
        return 0;
    }

    size_t active_queries = ares_queue_active_queries(channel);
    ares_cancel(channel);

    ares_destroy(channel);
    return 0;
}