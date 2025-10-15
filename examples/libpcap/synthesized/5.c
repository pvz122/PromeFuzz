// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
// pcap_list_datalinks at pcap.c:2954:1 in pcap.h
// pcap_statustostr at pcap.c:3633:1 in pcap.h
// pcap_geterr at pcap.c:3528:1 in pcap.h
// pcap_datalink_val_to_name at pcap.c:3343:1 in pcap.h
// pcap_free_datalinks at pcap.c:2998:1 in pcap.h
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

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (!pcap) return 0;

    char *err = pcap_geterr(pcap);
    if (err) {
        // Do nothing, just to trigger pcap_geterr
    }

    int *dlt_buf;
    int dlt_count = pcap_list_datalinks(pcap, &dlt_buf);
    if (dlt_count > 0) {
        const char *status_str = pcap_statustostr(dlt_count);
        if (status_str) {
            // Do nothing, just to trigger pcap_statustostr
        }

        err = pcap_geterr(pcap);
        if (err) {
            // Do nothing, just to trigger pcap_geterr
        }

        for (int i = 0; i < dlt_count; i++) {
            const char *dlt_name = pcap_datalink_val_to_name(dlt_buf[i]);
            if (dlt_name) {
                // Do nothing, just to trigger pcap_datalink_val_to_name
            }
        }

        pcap_free_datalinks(dlt_buf);
    }

    pcap_close(pcap);
    return 0;
}