// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_datalink_val_to_name at pcap.c:3343:1 in pcap.h
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_dispatch at pcap.c:2893:1 in pcap.h
// pcap_stats at pcap.c:3827:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_freecode at gencode.c:1055:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>

static void dummy_callback(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    // Do nothing
}

int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    int dlt = *(int *)Data;
    const char *name = pcap_datalink_val_to_name(dlt);

    pcap_t *handle = pcap_open_dead(dlt, 65535);
    if (handle == NULL) {
        return 0;
    }

    pcap_dispatch(handle, 1, dummy_callback, NULL);

    struct pcap_stat stats;
    pcap_stats(handle, &stats);

    char *err = pcap_geterr(handle);
    err = pcap_geterr(handle);

    pcap_close(handle);

    struct bpf_program fp;
    pcap_freecode(&fp);

    return 0;
}