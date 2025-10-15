// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_findalldevs_ex at pcap.c:4602:1 in pcap.h
// pcap_findalldevs at pcap.c:672:1 in pcap.h
// pcap_freealldevs at pcap.c:1414:1 in pcap.h
// pcap_lookupnet at pcap.c:1547:1 in pcap.h
// pcap_freealldevs at pcap.c:1414:1 in pcap.h
// pcap_freealldevs at pcap.c:1414:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char source[PCAP_BUF_SIZE + 1];
    size_t source_len = Size < PCAP_BUF_SIZE ? Size : PCAP_BUF_SIZE;
    memcpy(source, Data, source_len);
    source[source_len] = '\0';

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs = NULL;
    struct pcap_rmtauth auth = {0, NULL, NULL};
    bpf_u_int32 net, mask;

    // pcap_findalldevs_ex
    int ret = pcap_findalldevs_ex(source, &auth, &alldevs, errbuf);
    if (ret == -1) {
        return 0;
    }

    // pcap_findalldevs
    pcap_if_t *alldevs2 = NULL;
    ret = pcap_findalldevs(&alldevs2, errbuf);
    if (ret == -1) {
        pcap_freealldevs(alldevs);
        return 0;
    }

    // pcap_lookupnet
    if (alldevs != NULL) {
        pcap_lookupnet(alldevs->name, &net, &mask, errbuf);
    }

    // pcap_freealldevs
    pcap_freealldevs(alldevs);
    pcap_freealldevs(alldevs2);

    return 0;
}