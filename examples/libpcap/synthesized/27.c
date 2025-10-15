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

int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char *source = (char *)malloc(Size + 1);
    if (!source) return 0;
    memcpy(source, Data, Size);
    source[Size] = '\0';

    int type;
    char host[256];
    char port[256];
    char name[256];
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_parsesrcstr(source, &type, host, port, name, errbuf);

    pcap_t *pcap = pcap_open_live("any", 65535, 1, 1000, errbuf);
    if (pcap) {
        pcap_set_buffer_size(pcap, 1024 * 1024);
        pcap_close(pcap);
    }

    pcap_if_t *alldevs;
    struct pcap_rmtauth auth = {0};
    pcap_findalldevs_ex(source, &auth, &alldevs, errbuf);
    if (alldevs) {
        pcap_freealldevs(alldevs);
    }

    char created_source[256];
    pcap_createsrcstr(created_source, type, host, port, name, errbuf);

    pcap_t *pcap_open_handle = pcap_open(source, 65535, PCAP_OPENFLAG_PROMISCUOUS, 1000, &auth, errbuf);
    if (pcap_open_handle) {
        pcap_close(pcap_open_handle);
    }

    free(source);
    return 0;
}