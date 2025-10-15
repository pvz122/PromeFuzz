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
#include "namedb.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a null-terminated string from the input data
    char *input_str = (char *)malloc(Size + 1);
    if (!input_str) return 0;
    memcpy(input_str, Data, Size);
    input_str[Size] = '\0';

    // Fuzz pcap_nametollc
    pcap_nametollc(input_str);

    // Fuzz pcap_nametoeproto
    pcap_nametoeproto(input_str);

    // Fuzz pcap_nametoport
    int port_tcp, port_udp;
    pcap_nametoport(input_str, &port_tcp, &port_udp);

    // Fuzz pcap_nametonetaddr
    pcap_nametonetaddr(input_str);

    // Fuzz pcap_nametoproto
    pcap_nametoproto(input_str);

    // Fuzz pcap_nametoportrange
    int start_port, end_port, protocol;
    pcap_nametoportrange(input_str, &start_port, &end_port, &protocol);

    free(input_str);
    return 0;
}