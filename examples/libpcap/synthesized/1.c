// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// bpf_validate at bpf_filter.c:541:1 in bpf.h
// bpf_dump at bpf_dump.c:30:1 in bpf.h
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_next_ex at pcap.c:568:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
// pcap_offline_filter at pcap.c:4257:1 in pcap.h
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
#include <pcap.h>
#include <bpf.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct bpf_insn)) return 0;

    struct bpf_insn *insns = (struct bpf_insn *)malloc(Size);
    if (!insns) return 0;
    memcpy(insns, Data, Size);

    int len = Size / sizeof(struct bpf_insn);

    if (!bpf_validate(insns, len)) {
        free(insns);
        return 0;
    }

    struct bpf_program program;
    program.bf_len = len;
    program.bf_insns = insns;

    bpf_dump(&program, 2);

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (!pcap) {
        free(insns);
        return 0;
    }

    struct pcap_pkthdr pkthdr;
    const u_char *pkt_data = Data;
    pkthdr.caplen = Size;
    pkthdr.len = Size;

    int ret = pcap_next_ex(pcap, &pkthdr, &pkt_data);
    if (ret == -1) {
        pcap_geterr(pcap);
    }

    if (pcap_offline_filter(&program, &pkthdr, pkt_data)) {
        // Filter matched
    }

    pcap_freecode(&program);
    pcap_close(pcap);

    return 0;
}