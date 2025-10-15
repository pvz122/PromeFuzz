// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_setnonblock at pcap.c:3578:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_setnonblock at pcap.c:3578:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_findalldevs at pcap.c:672:1 in pcap.h
// pcap_freealldevs at pcap.c:1414:1 in pcap.h
// pcap_create at pcap.c:2242:1 in pcap.h
// pcap_setnonblock at pcap.c:3578:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_getnonblock at pcap.c:3534:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_activate at pcap.c:2695:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_getnonblock at pcap.c:3534:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_setnonblock at pcap.c:3578:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_getnonblock at pcap.c:3534:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_setnonblock at pcap.c:3578:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_getnonblock at pcap.c:3534:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_loop at pcap.c:2899:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void dummy_handler(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    // Do nothing
}

int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    pcap_if_t *alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];
    int ret;

    // pcap_findalldevs
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        return 0;
    }

    // pcap_freealldevs
    pcap_freealldevs(alldevs);

    // pcap_create
    pcap_t *pcap = pcap_create(NULL, errbuf);
    if (pcap == NULL) {
        return 0;
    }

    // pcap_setnonblock
    ret = pcap_setnonblock(pcap, 1, errbuf);
    if (ret != 0) {
        pcap_close(pcap);
        return 0;
    }

    // pcap_getnonblock
    ret = pcap_getnonblock(pcap, errbuf);
    if (ret < 0) {
        pcap_close(pcap);
        return 0;
    }

    // pcap_activate
    ret = pcap_activate(pcap);
    if (ret < 0) {
        pcap_close(pcap);
        return 0;
    }

    // pcap_getnonblock
    ret = pcap_getnonblock(pcap, errbuf);
    if (ret < 0) {
        pcap_close(pcap);
        return 0;
    }

    // pcap_setnonblock
    ret = pcap_setnonblock(pcap, 0, errbuf);
    if (ret != 0) {
        pcap_close(pcap);
        return 0;
    }

    // pcap_getnonblock
    ret = pcap_getnonblock(pcap, errbuf);
    if (ret < 0) {
        pcap_close(pcap);
        return 0;
    }

    // pcap_setnonblock
    ret = pcap_setnonblock(pcap, 1, errbuf);
    if (ret != 0) {
        pcap_close(pcap);
        return 0;
    }

    // pcap_getnonblock
    ret = pcap_getnonblock(pcap, errbuf);
    if (ret < 0) {
        pcap_close(pcap);
        return 0;
    }

    // pcap_loop
    ret = pcap_loop(pcap, 1, dummy_handler, NULL);
    if (ret < 0) {
        pcap_close(pcap);
        return 0;
    }

    // pcap_geterr
    char *err = pcap_geterr(pcap);
    if (err == NULL) {
        pcap_close(pcap);
        return 0;
    }

    // pcap_setnonblock
    ret = pcap_setnonblock(pcap, 0, errbuf);
    if (ret != 0) {
        pcap_close(pcap);
        return 0;
    }

    // pcap_setnonblock
    ret = pcap_setnonblock(pcap, 1, errbuf);
    if (ret != 0) {
        pcap_close(pcap);
        return 0;
    }

    pcap_close(pcap);
    return 0;
}