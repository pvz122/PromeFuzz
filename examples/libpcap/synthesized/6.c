// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_compile at gencode.c:863:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_setfilter at pcap.c:3786:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
// pcap_get_selectable_fd at pcap.c:3509:1 in pcap.h
// pcap_get_required_select_timeout at pcap.c:3515:1 in pcap.h
// pcap_setnonblock at pcap.c:3578:1 in pcap.h
// pcap_get_required_select_timeout at pcap.c:3515:1 in pcap.h
// pcap_dispatch at pcap.c:2893:1 in pcap.h
// pcap_get_required_select_timeout at pcap.c:3515:1 in pcap.h
// pcap_dispatch at pcap.c:2893:1 in pcap.h
// pcap_dispatch at pcap.c:2893:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_freecode at gencode.c:1055:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void dummy_callback(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    // Do nothing
}

int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (!pcap) return 0;

    struct bpf_program filter;
    char *filter_str = (char *)malloc(Size + 1);
    if (!filter_str) {
        pcap_close(pcap);
        return 0;
    }
    memcpy(filter_str, Data, Size);
    filter_str[Size] = '\0';

    if (pcap_compile(pcap, &filter, filter_str, 1, PCAP_NETMASK_UNKNOWN) == -1) {
        free(filter_str);
        pcap_close(pcap);
        return 0;
    }

    pcap_setfilter(pcap, &filter);
    pcap_geterr(pcap);
    pcap_get_selectable_fd(pcap);
    pcap_get_required_select_timeout(pcap);
    pcap_setnonblock(pcap, 1, errbuf);
    pcap_get_required_select_timeout(pcap);
    pcap_dispatch(pcap, 1, dummy_callback, NULL);
    pcap_get_required_select_timeout(pcap);
    pcap_dispatch(pcap, 1, dummy_callback, NULL);
    pcap_dispatch(pcap, 1, dummy_callback, NULL);
    pcap_geterr(pcap);
    pcap_close(pcap);

    pcap_freecode(&filter);
    free(filter_str);
    return 0;
}