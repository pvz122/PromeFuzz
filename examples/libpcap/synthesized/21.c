// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_live at pcap.c:2749:1 in pcap.h
// pcap_set_promisc at pcap.c:2544:1 in pcap.h
// pcap_set_snaplen at pcap.c:2535:1 in pcap.h
// pcap_set_timeout at pcap.c:2562:1 in pcap.h
// pcap_set_rfmon at pcap.c:2553:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap_handle = pcap_open_live("any", 65535, 1, 1000, errbuf);
    if (pcap_handle == NULL) return 0;

    int promisc = Data[0] & 1;
    int snaplen = (Data[0] >> 1) & 0x7F;
    int timeout = (Data[0] >> 8) & 0x7F;
    int rfmon = (Data[0] >> 16) & 1;

    pcap_set_promisc(pcap_handle, promisc);
    pcap_set_snaplen(pcap_handle, snaplen);
    pcap_set_timeout(pcap_handle, timeout);
    pcap_set_rfmon(pcap_handle, rfmon);

    pcap_close(pcap_handle);

    return 0;
}