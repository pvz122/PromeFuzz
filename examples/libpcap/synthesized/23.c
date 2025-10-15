// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_parsesrcstr at pcap.c:2235:1 in pcap.h
// pcap_open_live at pcap.c:2749:1 in pcap.h
// pcap_set_buffer_size at pcap.c:2625:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_findalldevs_ex at pcap.c:4602:1 in pcap.h
// pcap_freealldevs at pcap.c:1414:1 in pcap.h
// pcap_createsrcstr at pcap.c:2121:1 in pcap.h
// pcap_open at pcap.c:4928:1 in pcap.h
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

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char *source = malloc(Size + 1);
    if (!source) return 0;
    memcpy(source, Data, Size);
    source[Size] = '\0';

    char errbuf[PCAP_ERRBUF_SIZE];
    int type;
    char host[256], port[256], name[256];

    pcap_parsesrcstr(source, &type, host, port, name, errbuf);

    pcap_t *pcap = pcap_open_live("any", 65536, 1, 1000, errbuf);
    if (pcap) {
        pcap_set_buffer_size(pcap, 1024 * 1024);
        pcap_close(pcap);
    }

    pcap_if_t *alldevs;
    pcap_findalldevs_ex(source, NULL, &alldevs, errbuf);
    if (alldevs) {
        pcap_freealldevs(alldevs);
    }

    char srcstr[256];
    pcap_createsrcstr(srcstr, PCAP_SRC_IFLOCAL, "localhost", "1234", "eth0", errbuf);

    pcap_t *pcap2 = pcap_open(source, 65536, 1, 1000, NULL, errbuf);
    if (pcap2) {
        pcap_close(pcap2);
    }

    free(source);
    return 0;
}