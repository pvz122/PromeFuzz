// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_create at pcap.c:2242:1 in pcap.h
// pcap_set_protocol_linux at pcap-linux.c:6132:1 in pcap.h
// pcap_setdirection at pcap.c:3798:1 in pcap.h
// pcap_set_rfmon at pcap.c:2553:1 in pcap.h
// pcap_set_tstamp_precision at pcap.c:2640:1 in pcap.h
// pcap_set_snaplen at pcap.c:2535:1 in pcap.h
// pcap_set_promisc at pcap.c:2544:1 in pcap.h
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

int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_create("lo", errbuf);
    if (pcap == NULL) return 0;

    int protocol = (int)Data[0];
    pcap_set_protocol_linux(pcap, protocol);

    pcap_direction_t direction = (pcap_direction_t)(Data[0] % 3);
    pcap_setdirection(pcap, direction);

    int rfmon = (int)Data[0] % 2;
    pcap_set_rfmon(pcap, rfmon);

    int tstamp_precision = (int)Data[0] % 2;
    pcap_set_tstamp_precision(pcap, tstamp_precision);

    int snaplen = (int)Data[0] % 65536;
    pcap_set_snaplen(pcap, snaplen);

    int promisc = (int)Data[0] % 2;
    pcap_set_promisc(pcap, promisc);

    pcap_close(pcap);
    return 0;
}