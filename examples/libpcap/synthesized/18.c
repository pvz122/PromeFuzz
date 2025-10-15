// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_offline_with_tstamp_precision at savefile.c:335:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_open_offline at savefile.c:388:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_fopen_offline_with_tstamp_precision at savefile.c:467:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_fopen_offline at savefile.c:600:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_open_live at pcap.c:2749:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_open_offline at savefile.c:388:1 in pcap.h
// pcap_next_ex at pcap.c:568:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Test pcap_open_offline_with_tstamp_precision
    pcap_t *pcap1 = pcap_open_offline_with_tstamp_precision("./dummy_file", PCAP_TSTAMP_PRECISION_MICRO, errbuf);
    if (pcap1) {
        pcap_close(pcap1);
    }

    // Test pcap_open_offline
    pcap_t *pcap2 = pcap_open_offline("./dummy_file", errbuf);
    if (pcap2) {
        pcap_close(pcap2);
    }

    // Test pcap_fopen_offline_with_tstamp_precision
    FILE *f = fopen("./dummy_file", "rb");
    if (f) {
        pcap_t *pcap3 = pcap_fopen_offline_with_tstamp_precision(f, PCAP_TSTAMP_PRECISION_MICRO, errbuf);
        if (pcap3) {
            pcap_close(pcap3);
        } else {
            fclose(f);
        }
    }

    // Test pcap_fopen_offline
    f = fopen("./dummy_file", "rb");
    if (f) {
        pcap_t *pcap4 = pcap_fopen_offline(f, errbuf);
        if (pcap4) {
            pcap_close(pcap4);
        } else {
            fclose(f);
        }
    }

    // Test pcap_open_live
    pcap_t *pcap5 = pcap_open_live("any", 65535, 1, 1000, errbuf);
    if (pcap5) {
        pcap_close(pcap5);
    }

    // Test pcap_next_ex
    pcap_t *pcap6 = pcap_open_offline("./dummy_file", errbuf);
    if (pcap6) {
        struct pcap_pkthdr *header;
        const u_char *data;
        while (pcap_next_ex(pcap6, &header, &data) > 0) {
            // Do nothing, just read packets
        }
        pcap_close(pcap6);
    }

    return 0;
}