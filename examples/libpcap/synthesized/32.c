// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_offline_with_tstamp_precision at savefile.c:335:1 in pcap.h
// pcap_next_ex at pcap.c:568:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_open_offline at savefile.c:388:1 in pcap.h
// pcap_next_ex at pcap.c:568:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_fopen_offline_with_tstamp_precision at savefile.c:467:1 in pcap.h
// pcap_next_ex at pcap.c:568:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_fopen_offline at savefile.c:600:1 in pcap.h
// pcap_next_ex at pcap.c:568:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_open_live at pcap.c:2749:1 in pcap.h
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
#include <string.h>

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return;
    fwrite(data, 1, size, file);
    fclose(file);
}

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap_handle;
    struct pcap_pkthdr *header;
    const u_char *packet;

    // Test pcap_open_offline_with_tstamp_precision
    write_dummy_file(data, size);
    pcap_handle = pcap_open_offline_with_tstamp_precision("./dummy_file", PCAP_TSTAMP_PRECISION_MICRO, errbuf);
    if (pcap_handle) {
        while (pcap_next_ex(pcap_handle, &header, &packet) > 0) {}
        pcap_close(pcap_handle);
    }

    // Test pcap_open_offline
    write_dummy_file(data, size);
    pcap_handle = pcap_open_offline("./dummy_file", errbuf);
    if (pcap_handle) {
        while (pcap_next_ex(pcap_handle, &header, &packet) > 0) {}
        pcap_close(pcap_handle);
    }

    // Test pcap_fopen_offline_with_tstamp_precision
    write_dummy_file(data, size);
    FILE *file = fopen("./dummy_file", "rb");
    if (file) {
        pcap_handle = pcap_fopen_offline_with_tstamp_precision(file, PCAP_TSTAMP_PRECISION_MICRO, errbuf);
        if (pcap_handle) {
            while (pcap_next_ex(pcap_handle, &header, &packet) > 0) {}
            pcap_close(pcap_handle);
        }
        fclose(file);
    }

    // Test pcap_fopen_offline
    write_dummy_file(data, size);
    file = fopen("./dummy_file", "rb");
    if (file) {
        pcap_handle = pcap_fopen_offline(file, errbuf);
        if (pcap_handle) {
            while (pcap_next_ex(pcap_handle, &header, &packet) > 0) {}
            pcap_close(pcap_handle);
        }
        fclose(file);
    }

    // Test pcap_open_live
    pcap_handle = pcap_open_live("any", 65535, 1, 1000, errbuf);
    if (pcap_handle) {
        while (pcap_next_ex(pcap_handle, &header, &packet) > 0) {}
        pcap_close(pcap_handle);
    }

    return 0;
}