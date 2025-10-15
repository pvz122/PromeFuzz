// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_compile at gencode.c:863:1 in pcap.h
// pcap_perror at pcap.c:3522:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_setfilter at pcap.c:3786:1 in pcap.h
// pcap_perror at pcap.c:3522:1 in pcap.h
// pcap_freecode at gencode.c:1055:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
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

int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (!pcap) return 0;

    struct bpf_program fp;
    char *filter = (char *)malloc(Size + 1);
    if (!filter) {
        pcap_close(pcap);
        return 0;
    }
    memcpy(filter, Data, Size);
    filter[Size] = '\0';

    if (pcap_compile(pcap, &fp, filter, 1, PCAP_NETMASK_UNKNOWN) == -1) {
        pcap_perror(pcap, "Error compiling filter");
        free(filter);
        pcap_close(pcap);
        return 0;
    }

    if (pcap_setfilter(pcap, &fp) == -1) {
        pcap_perror(pcap, "Error setting filter");
        pcap_freecode(&fp);
        free(filter);
        pcap_close(pcap);
        return 0;
    }

    pcap_freecode(&fp);
    free(filter);
    pcap_close(pcap);

    return 0;
}