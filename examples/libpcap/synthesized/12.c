// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_compile at gencode.c:863:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_setfilter at pcap.c:3786:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
// pcap_freecode at gencode.c:1055:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_dump_open at sf-pcap.c:902:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
// pcap_freecode at gencode.c:1055:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_datalink at pcap.c:2938:1 in pcap.h
// pcap_dump_close at sf-pcap.c:1262:1 in pcap.h
// pcap_freecode at gencode.c:1055:1 in pcap.h
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

int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap == NULL) return 0;

    struct bpf_program fp;
    char filter[Size + 1];
    memcpy(filter, Data, Size);
    filter[Size] = '\0';

    if (pcap_compile(pcap, &fp, filter, 1, PCAP_NETMASK_UNKNOWN) == -1) {
        pcap_geterr(pcap);
        pcap_close(pcap);
        return 0;
    }

    if (pcap_setfilter(pcap, &fp) == -1) {
        pcap_geterr(pcap);
        pcap_freecode(&fp);
        pcap_close(pcap);
        return 0;
    }

    pcap_dumper_t *dumper = pcap_dump_open(pcap, "./dummy_file");
    if (dumper == NULL) {
        pcap_geterr(pcap);
        pcap_freecode(&fp);
        pcap_close(pcap);
        return 0;
    }

    pcap_datalink(pcap);

    pcap_dump_close(dumper);
    pcap_freecode(&fp);
    pcap_close(pcap);

    return 0;
}