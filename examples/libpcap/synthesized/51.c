// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_fopen_offline_with_tstamp_precision at savefile.c:467:1 in pcap.h
// pcap_file at pcap.c:3474:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_open_offline at savefile.c:388:1 in pcap.h
// pcap_next_ex at pcap.c:568:1 in pcap.h
// pcap_loop at pcap.c:2899:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void packet_handler(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    // Do nothing with the packet
}

int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    file = fopen("./dummy_file", "rb");
    if (!file) return 0;

    pcap_t *pcap = pcap_fopen_offline_with_tstamp_precision(file, PCAP_TSTAMP_PRECISION_MICRO, errbuf);
    if (!pcap) {
        fclose(file);
        return 0;
    }

    FILE *retrieved_file = pcap_file(pcap);
    if (retrieved_file != file) {
        pcap_close(pcap);
        return 0;
    }

    pcap_t *pcap_offline = pcap_open_offline("./dummy_file", errbuf);
    if (pcap_offline) {
        struct pcap_pkthdr *header;
        const u_char *packet;
        int ret = pcap_next_ex(pcap_offline, &header, &packet);
        if (ret == 1) {
            // Packet read successfully
        }
        pcap_loop(pcap_offline, 1, packet_handler, NULL);
        pcap_close(pcap_offline);
    }

    pcap_close(pcap);
    return 0;
}