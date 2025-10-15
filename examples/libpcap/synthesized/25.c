// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// bpf_validate at bpf_filter.c:541:1 in bpf.h
// pcap_compile at gencode.c:863:1 in pcap.h
// pcap_setfilter at pcap.c:3786:1 in pcap.h
// pcap_offline_filter at pcap.c:4257:1 in pcap.h
// bpf_dump at bpf_dump.c:30:1 in bpf.h
// bpf_image at bpf_image.c:130:1 in bpf.h
// pcap_freecode at gencode.c:1055:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "pcap.h"
#include "bpf.h"

int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct bpf_insn)) {
        return 0;
    }

    // Initialize pcap_t
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap == NULL) {
        return 0;
    }

    // Initialize bpf_program
    struct bpf_program bpf_prog;
    memset(&bpf_prog, 0, sizeof(bpf_prog));

    // Initialize bpf_insn
    struct bpf_insn *bpf_insns = (struct bpf_insn *)Data;
    int bpf_insns_len = Size / sizeof(struct bpf_insn);

    // Fuzz bpf_validate
    bpf_validate(bpf_insns, bpf_insns_len);

    // Fuzz pcap_compile
    pcap_compile(pcap, &bpf_prog, "ip", 1, 0);

    // Fuzz pcap_setfilter
    pcap_setfilter(pcap, &bpf_prog);

    // Fuzz pcap_offline_filter
    struct pcap_pkthdr pkthdr;
    memset(&pkthdr, 0, sizeof(pkthdr));
    pkthdr.caplen = Size;
    pkthdr.len = Size;
    pcap_offline_filter(&bpf_prog, &pkthdr, Data);

    // Fuzz bpf_dump
    bpf_dump(&bpf_prog, 1);

    // Fuzz bpf_image
    char *image = bpf_image(bpf_insns, bpf_insns_len);
    // Do not free image as it is not malloc()-ed by us

    // Cleanup
    pcap_freecode(&bpf_prog);
    pcap_close(pcap);

    return 0;
}