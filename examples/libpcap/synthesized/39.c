// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4518:1 in pcap.h
// pcap_set_datalink at pcap.c:3004:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_dump_fopen at sf-pcap.c:988:1 in pcap.h
// pcap_dump_flush at sf-pcap.c:1252:1 in pcap.h
// pcap_dump_close at sf-pcap.c:1262:1 in pcap.h
// pcap_set_buffer_size at pcap.c:2625:1 in pcap.h
// pcap_fileno at pcap.c:3501:1 in pcap.h
// pcap_bufsize at pcap.c:3466:1 in pcap.h
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

int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap == NULL) return 0;

    int datalink = (int)Data[0] % 256;
    pcap_set_datalink(pcap, datalink);

    FILE *file = fopen("./dummy_file", "wb");
    if (file == NULL) {
        pcap_close(pcap);
        return 0;
    }
    pcap_dumper_t *dumper = pcap_dump_fopen(pcap, file);
    if (dumper != NULL) {
        pcap_dump_flush(dumper);
        pcap_dump_close(dumper);
    } else {
        fclose(file);
    }

    int bufsize = (int)Data[0] % 65536;
    pcap_set_buffer_size(pcap, bufsize);

    int fd = pcap_fileno(pcap);

    int current_bufsize = pcap_bufsize(pcap);

    pcap_close(pcap);
    return 0;
}