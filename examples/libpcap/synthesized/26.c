// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_activate at pcap.c:2695:1 in pcap.h
// pcap_list_datalinks at pcap.c:2954:1 in pcap.h
// pcap_set_datalink at pcap.c:3004:1 in pcap.h
// pcap_datalink at pcap.c:2938:1 in pcap.h
// pcap_free_datalinks at pcap.c:2998:1 in pcap.h
// pcap_free_tstamp_types at pcap.c:534:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (!pcap) return 0;

    // Fuzz pcap_activate
    pcap_activate(pcap);

    // Fuzz pcap_list_datalinks
    int *dlt_buf;
    int dlt_count = pcap_list_datalinks(pcap, &dlt_buf);
    if (dlt_count > 0) {
        // Fuzz pcap_set_datalink
        pcap_set_datalink(pcap, dlt_buf[Size % dlt_count]);

        // Fuzz pcap_datalink
        pcap_datalink(pcap);

        // Fuzz pcap_free_datalinks
        pcap_free_datalinks(dlt_buf);
    }

    // Fuzz pcap_free_tstamp_types
    int *tstamp_types = (int *)malloc(sizeof(int) * 10);
    if (tstamp_types) {
        pcap_free_tstamp_types(tstamp_types);
    }

    pcap_close(pcap);
    return 0;
}