// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_set_immediate_mode at pcap.c:2616:1 in pcap.h
// pcap_set_immediate_mode at pcap.c:2616:1 in pcap.h
// pcap_statustostr at pcap.c:3633:1 in pcap.h
// pcap_set_timeout at pcap.c:2562:1 in pcap.h
// pcap_set_timeout at pcap.c:2562:1 in pcap.h
// pcap_statustostr at pcap.c:3633:1 in pcap.h
// pcap_activate at pcap.c:2695:1 in pcap.h
// pcap_activate at pcap.c:2695:1 in pcap.h
// pcap_statustostr at pcap.c:3633:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
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

int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(int)) {
        return 0;
    }

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap == NULL) {
        return 0;
    }

    int immediate_mode = *(int *)Data;
    int timeout = *(int *)(Data + sizeof(int));

    pcap_set_immediate_mode(pcap, immediate_mode);
    pcap_statustostr(pcap_set_immediate_mode(pcap, immediate_mode));

    pcap_set_timeout(pcap, timeout);
    pcap_statustostr(pcap_set_timeout(pcap, timeout));

    pcap_activate(pcap);
    pcap_statustostr(pcap_activate(pcap));

    pcap_geterr(pcap);

    pcap_close(pcap);
    return 0;
}