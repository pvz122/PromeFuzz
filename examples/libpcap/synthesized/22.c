// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_activate at pcap.c:2695:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_lookupdev at pcap.c:1471:1 in pcap.h
// pcap_lookupnet at pcap.c:1547:1 in pcap.h
// pcap_findalldevs_ex at pcap.c:4602:1 in pcap.h
// pcap_freealldevs at pcap.c:1414:1 in pcap.h
// pcap_findalldevs at pcap.c:672:1 in pcap.h
// pcap_freealldevs at pcap.c:1414:1 in pcap.h
// pcap_open_live at pcap.c:2749:1 in pcap.h
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

static void fuzz_pcap_activate(const uint8_t *data, size_t size) {
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap) {
        pcap_activate(pcap);
        pcap_close(pcap);
    }
}

static void fuzz_pcap_lookupdev(const uint8_t *data, size_t size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    char *dev = pcap_lookupdev(errbuf);
    (void)dev;
}

static void fuzz_pcap_lookupnet(const uint8_t *data, size_t size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    bpf_u_int32 net, mask;
    pcap_lookupnet("lo", &net, &mask, errbuf);
}

static void fuzz_pcap_findalldevs_ex(const uint8_t *data, size_t size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs;
    struct pcap_rmtauth auth = {0};
    pcap_findalldevs_ex("rpcap://", &auth, &alldevs, errbuf);
    if (alldevs) {
        pcap_freealldevs(alldevs);
    }
}

static void fuzz_pcap_findalldevs(const uint8_t *data, size_t size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs;
    pcap_findalldevs(&alldevs, errbuf);
    if (alldevs) {
        pcap_freealldevs(alldevs);
    }
}

static void fuzz_pcap_open_live(const uint8_t *data, size_t size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_live("lo", 65535, 1, 1000, errbuf);
    if (pcap) {
        pcap_close(pcap);
    }
}

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    if (size == 0) return 0;

    fuzz_pcap_activate(data, size);
    fuzz_pcap_lookupdev(data, size);
    fuzz_pcap_lookupnet(data, size);
    fuzz_pcap_findalldevs_ex(data, size);
    fuzz_pcap_findalldevs(data, size);
    fuzz_pcap_open_live(data, size);

    return 0;
}