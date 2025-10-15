// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_set_protocol_linux at pcap-linux.c:6132:1 in pcap.h
// pcap_set_immediate_mode at pcap.c:2616:1 in pcap.h
// pcap_set_timeout at pcap.c:2562:1 in pcap.h
// pcap_set_promisc at pcap.c:2544:1 in pcap.h
// pcap_activate at pcap.c:2695:1 in pcap.h
// pcap_datalink_ext at pcap.c:2946:1 in pcap.h
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

int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (!pcap) return 0;

    int protocol = Data[0] & 0xFF;
    pcap_set_protocol_linux(pcap, protocol);

    int immediate_mode = Data[0] & 0x01;
    pcap_set_immediate_mode(pcap, immediate_mode);

    int timeout = (Data[0] & 0xFF) + 1;
    pcap_set_timeout(pcap, timeout);

    int promisc = Data[0] & 0x01;
    pcap_set_promisc(pcap, promisc);

    int activate_result = pcap_activate(pcap);
    if (activate_result >= 0) {
        pcap_datalink_ext(pcap);
    }

    pcap_close(pcap);
    return 0;
}