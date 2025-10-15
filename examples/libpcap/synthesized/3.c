// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_live at pcap.c:2749:1 in pcap.h
// pcap_statustostr at pcap.c:3633:1 in pcap.h
// pcap_set_timeout at pcap.c:2562:1 in pcap.h
// pcap_statustostr at pcap.c:3633:1 in pcap.h
// pcap_set_buffer_size at pcap.c:2625:1 in pcap.h
// pcap_statustostr at pcap.c:3633:1 in pcap.h
// pcap_activate at pcap.c:2695:1 in pcap.h
// pcap_statustostr at pcap.c:3633:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
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

int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap_handle = NULL;
    int timeout = (int)Data[0];
    int buffer_size = (int)Data[0] * 1024;
    const char *device = "lo";

    pcap_handle = pcap_open_live(device, 65535, 1, timeout, errbuf);
    if (pcap_handle == NULL) return 0;

    pcap_statustostr(0);
    pcap_set_timeout(pcap_handle, timeout);
    pcap_statustostr(0);
    pcap_set_buffer_size(pcap_handle, buffer_size);
    pcap_statustostr(0);
    pcap_activate(pcap_handle);
    pcap_statustostr(0);
    pcap_geterr(pcap_handle);
    pcap_statustostr(0);
    pcap_geterr(pcap_handle);

    pcap_close(pcap_handle);

    return 0;
}