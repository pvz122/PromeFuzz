// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_lookupnet at pcap.c:1547:1 in pcap.h
// pcap_datalink_name_to_val at pcap.c:3331:1 in pcap.h
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_set_datalink at pcap.c:3004:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
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

int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pcap_t *pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) return 0;

    pcap_close(pcap_handle);

    char device[256];
    bpf_u_int32 net, mask;
    char errbuf[PCAP_ERRBUF_SIZE];

    memcpy(device, Data, Size < sizeof(device) ? Size : sizeof(device) - 1);
    device[sizeof(device) - 1] = '\0';

    pcap_lookupnet(device, &net, &mask, errbuf);

    const char *datalink_name = "EN10MB";
    int datalink_val = pcap_datalink_name_to_val(datalink_name);

    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) return 0;

    pcap_set_datalink(pcap_handle, datalink_val);

    char *error = pcap_geterr(pcap_handle);
    (void)error;

    pcap_close(pcap_handle);

    return 0;
}