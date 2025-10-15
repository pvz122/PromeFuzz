// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_statustostr at pcap.c:3633:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_statustostr at pcap.c:3633:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
// pcap_lookupnet at pcap.c:1547:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_compile at gencode.c:863:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
// pcap_setfilter at pcap.c:3786:1 in pcap.h
// pcap_freecode at gencode.c:1055:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
// pcap_breakloop at pcap.c:2932:1 in pcap.h
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

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap;
    struct bpf_program fp;
    bpf_u_int32 net, mask;
    const char *status_str;
    char *err;

    // Initialize pcap handle
    pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap == NULL) return 0;

    // Call pcap_statustostr
    status_str = pcap_statustostr((int)Data[0] % 100);
    if (status_str == NULL) {
        pcap_close(pcap);
        return 0;
    }

    // Call pcap_geterr
    err = pcap_geterr(pcap);
    if (err == NULL) {
        pcap_close(pcap);
        return 0;
    }

    // Call pcap_statustostr again
    status_str = pcap_statustostr((int)Data[0] % 100);

    // Call pcap_geterr again
    err = pcap_geterr(pcap);

    // Call pcap_lookupnet
    if (pcap_lookupnet("lo", &net, &mask, errbuf) == -1) {
        pcap_close(pcap);
        return 0;
    }

    // Call pcap_compile
    if (pcap_compile(pcap, &fp, "port 80", 1, mask) == -1) {
        pcap_close(pcap);
        return 0;
    }

    // Call pcap_geterr
    err = pcap_geterr(pcap);

    // Call pcap_setfilter
    if (pcap_setfilter(pcap, &fp) == -1) {
        pcap_freecode(&fp);
        pcap_close(pcap);
        return 0;
    }

    // Call pcap_geterr
    err = pcap_geterr(pcap);

    // Call pcap_breakloop
    pcap_breakloop(pcap);

    // Call pcap_close
    pcap_close(pcap);

    // Call pcap_freecode
    pcap_freecode(&fp);

    return 0;
}