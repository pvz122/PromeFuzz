// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_create at pcap.c:2242:1 in pcap.h
// pcap_set_protocol_linux at pcap-linux.c:6132:1 in pcap.h
// pcap_set_immediate_mode at pcap.c:2616:1 in pcap.h
// pcap_set_rfmon at pcap.c:2553:1 in pcap.h
// pcap_set_tstamp_precision at pcap.c:2640:1 in pcap.h
// pcap_set_snaplen at pcap.c:2535:1 in pcap.h
// pcap_activate at pcap.c:2695:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_create("lo", errbuf);
    if (pcap == NULL) {
        return 0;
    }

    int protocol = Data[0] % 256;
    pcap_set_protocol_linux(pcap, protocol);

    int immediate_mode = Data[0] % 2;
    pcap_set_immediate_mode(pcap, immediate_mode);

    int rfmon = Data[0] % 2;
    pcap_set_rfmon(pcap, rfmon);

    int tstamp_precision = Data[0] % 2 ? PCAP_TSTAMP_PRECISION_MICRO : PCAP_TSTAMP_PRECISION_NANO;
    pcap_set_tstamp_precision(pcap, tstamp_precision);

    int snaplen = (Data[0] % 256) + 1;
    pcap_set_snaplen(pcap, snaplen);

    pcap_activate(pcap);

    pcap_close(pcap);
    return 0;
}