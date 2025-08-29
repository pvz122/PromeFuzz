// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_init at ares_init.c:67:5 in ares.h
// ares_destroy at ares_destroy.c:32:6 in ares.h
// ares_gethostbyname at ares_gethostbyname.c:99:6 in ares.h
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

static void host_callback(void *arg, int status, int timeouts, struct hostent *host) {
    // Dummy callback function
}

int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    ares_channel_t *channel;
    int status = ares_init(&channel);
    if (status != ARES_SUCCESS) {
        return 0;
    }

    char *name = (char *)malloc(Size + 1);
    if (!name) {
        ares_destroy(channel);
        return 0;
    }
    memcpy(name, Data, Size);
    name[Size] = '\0';

    ares_gethostbyname(channel, name, AF_INET, host_callback, NULL);

    free(name);
    ares_destroy(channel);

    return 0;
}