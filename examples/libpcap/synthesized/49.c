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

int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap_handle = pcap_create("lo", errbuf);
    if (pcap_handle == NULL) return 0;

    int protocol = Data[0] % 256;
    pcap_set_protocol_linux(pcap_handle, protocol);

    int direction = Data[0] % 3;
    pcap_setdirection(pcap_handle, direction);

    int rfmon = Data[0] % 2;
    pcap_set_rfmon(pcap_handle, rfmon);

    int tstamp_precision = Data[0] % 2;
    pcap_set_tstamp_precision(pcap_handle, tstamp_precision);

    int snaplen = Data[0] % 65536;
    pcap_set_snaplen(pcap_handle, snaplen);

    int promisc = Data[0] % 2;
    pcap_set_promisc(pcap_handle, promisc);

    pcap_close(pcap_handle);
    return 0;
}