// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_set_immediate_mode at pcap.c:2616:1 in pcap.h
// pcap_next at pcap.c:554:1 in pcap.h
// pcap_stats at pcap.c:3827:1 in pcap.h
// pcap_next_ex at pcap.c:568:1 in pcap.h
// pcap_loop at pcap.c:2899:1 in pcap.h
// pcap_dispatch at pcap.c:2893:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void dummy_pcap_handler(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    // Do nothing
}

int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (!pcap) return 0;

    int immediate_mode = Data[0] & 1;
    pcap_set_immediate_mode(pcap, immediate_mode);

    struct pcap_pkthdr hdr;
    const u_char *packet = pcap_next(pcap, &hdr);

    struct pcap_stat stats;
    pcap_stats(pcap, &stats);

    struct pcap_pkthdr *hdr_ptr;
    const u_char **packet_ptr;
    pcap_next_ex(pcap, &hdr_ptr, packet_ptr);

    pcap_loop(pcap, 1, dummy_pcap_handler, NULL);

    pcap_dispatch(pcap, 1, dummy_pcap_handler, NULL);

    pcap_close(pcap);
    return 0;
}