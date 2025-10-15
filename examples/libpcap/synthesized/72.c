// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_nametollc at nametoaddr.c:616:1 in namedb.h
// pcap_nametoeproto at nametoaddr.c:592:1 in namedb.h
// pcap_nametoport at nametoaddr.c:305:1 in namedb.h
// pcap_nametonetaddr at nametoaddr.c:221:1 in namedb.h
// pcap_nametoproto at nametoaddr.c:482:1 in namedb.h
// pcap_nametoportrange at nametoaddr.c:444:1 in namedb.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap/namedb.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_72(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    char *str = (char *)malloc(Size + 1);
    if (!str) return 0;
    memcpy(str, Data, Size);
    str[Size] = '\0';

    int port1, port2, proto;
    bpf_u_int32 netaddr;

    pcap_nametollc(str);
    pcap_nametoeproto(str);
    pcap_nametoport(str, &port1, &port2);
    pcap_nametonetaddr(str);
    pcap_nametoproto(str);
    pcap_nametoportrange(str, &port1, &port2, &proto);

    free(str);
    return 0;
}