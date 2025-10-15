// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_datalink_name_to_val at pcap.c:3331:1 in pcap.h
// pcap_tstamp_type_val_to_name at pcap.c:3410:1 in pcap.h
// pcap_datalink_val_to_name at pcap.c:3343:1 in pcap.h
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_datalink at pcap.c:2938:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_datalink_val_to_description at pcap.c:3355:1 in pcap.h
// pcap_datalink_val_to_description_or_dlt at pcap.c:3367:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // pcap_datalink_name_to_val
    char *datalink_name = (char *)malloc(Size + 1);
    if (datalink_name) {
        memcpy(datalink_name, Data, Size);
        datalink_name[Size] = '\0';
        pcap_datalink_name_to_val(datalink_name);
        free(datalink_name);
    }

    // pcap_tstamp_type_val_to_name
    int tstamp_type = *Data;
    pcap_tstamp_type_val_to_name(tstamp_type);

    // pcap_datalink_val_to_name
    int dlt = *Data;
    pcap_datalink_val_to_name(dlt);

    // pcap_datalink
    pcap_t *pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle) {
        pcap_datalink(pcap_handle);
        pcap_close(pcap_handle);
    }

    // pcap_datalink_val_to_description
    pcap_datalink_val_to_description(dlt);

    // pcap_datalink_val_to_description_or_dlt
    pcap_datalink_val_to_description_or_dlt(dlt);

    return 0;
}