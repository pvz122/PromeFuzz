// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_set_promisc at pcap.c:2544:1 in pcap.h
// pcap_set_buffer_size at pcap.c:2625:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_inject at pcap.c:4134:1 in pcap.h
// pcap_fileno at pcap.c:3501:1 in pcap.h
// pcap_set_rfmon at pcap.c:2553:1 in pcap.h
// pcap_set_datalink at pcap.c:3004:1 in pcap.h
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

int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap == NULL) return 0;

    int promisc = Data[0] & 1;
    pcap_set_promisc(pcap, promisc);

    int buffer_size = (int)Size;
    pcap_set_buffer_size(pcap, buffer_size);

    uint8_t *packet_data = (uint8_t *)malloc(Size);
    if (packet_data == NULL) {
        pcap_close(pcap);
        return 0;
    }
    memcpy(packet_data, Data, Size);
    pcap_inject(pcap, packet_data, Size);
    free(packet_data);

    pcap_fileno(pcap);

    int rfmon = Data[0] & 1;
    pcap_set_rfmon(pcap, rfmon);

    int datalink = DLT_EN10MB;
    pcap_set_datalink(pcap, datalink);

    pcap_close(pcap);
    return 0;
}