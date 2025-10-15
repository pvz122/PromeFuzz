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
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "namedb.h"

int LLVMFuzzerTestOneInput_77(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char *input = (char *)malloc(Size + 1);
    if (!input) return 0;
    memcpy(input, Data, Size);
    input[Size] = '\0';

    // Test pcap_nametollc
    pcap_nametollc(input);

    // Test pcap_nametoeproto
    pcap_nametoeproto(input);

    // Test pcap_nametoport
    int tcp_port, udp_port;
    pcap_nametoport(input, &tcp_port, &udp_port);

    // Test pcap_nametonetaddr
    pcap_nametonetaddr(input);

    // Test pcap_nametoproto
    pcap_nametoproto(input);

    // Test pcap_nametoportrange
    int start_port, end_port, protocol;
    pcap_nametoportrange(input, &start_port, &end_port, &protocol);

    free(input);
    return 0;
}