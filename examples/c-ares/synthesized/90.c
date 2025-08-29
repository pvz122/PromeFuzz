// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_init at ares_init.c:67:5 in ares.h
// ares_set_local_ip4 at ares_init.c:541:6 in ares.h
// ares_cancel at ares_cancel.c:34:6 in ares.h
// ares_set_local_ip6 at ares_init.c:552:6 in ares.h
// ares_set_local_dev at ares_init.c:563:6 in ares.h
// ares_reinit at ares_init.c:406:15 in ares.h
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

int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return 0;

    ares_channel_t *channel;
    int status = ares_init(&channel);
    if (status != ARES_SUCCESS) return 0;

    // Fuzz ares_set_local_ip4
    unsigned int local_ip4;
    memcpy(&local_ip4, Data, sizeof(unsigned int));
    ares_set_local_ip4(channel, local_ip4);

    // Fuzz ares_cancel
    ares_cancel(channel);

    // Fuzz ares_set_local_ip6
    unsigned char local_ip6[16];
    memcpy(local_ip6, Data, Size > 16 ? 16 : Size);
    ares_set_local_ip6(channel, local_ip6);

    // Fuzz ares_set_local_dev
    char local_dev_name[32];
    memcpy(local_dev_name, Data, Size > 31 ? 31 : Size);
    local_dev_name[Size > 31 ? 31 : Size] = '\0';
    ares_set_local_dev(channel, local_dev_name);

    // Fuzz ares_reinit
    ares_reinit(channel);

    ares_destroy(channel);
    return 0;
}