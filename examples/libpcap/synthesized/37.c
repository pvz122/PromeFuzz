// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_offline at savefile.c:388:1 in pcap.h
// pcap_dump_open at sf-pcap.c:902:1 in pcap.h
// pcap_dump_file at sf-pcap.c:1201:1 in pcap.h
// pcap_dump_ftell at sf-pcap.c:1207:1 in pcap.h
// pcap_dump_flush at sf-pcap.c:1252:1 in pcap.h
// pcap_dump_close at sf-pcap.c:1262:1 in pcap.h
// pcap_dump_open_append at sf-pcap.c:1005:1 in pcap.h
// pcap_dump_close at sf-pcap.c:1262:1 in pcap.h
// pcap_dump_fopen at sf-pcap.c:988:1 in pcap.h
// pcap_dump_close at sf-pcap.c:1262:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *fp = fopen("./dummy_file", "wb");
    if (fp) {
        fwrite(Data, 1, Size, fp);
        fclose(fp);
    }
}

int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    write_dummy_file(Data, Size);

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_offline("./dummy_file", errbuf);
    if (!pcap) return 0;

    pcap_dumper_t *dumper = pcap_dump_open(pcap, "./dummy_file");
    if (dumper) {
        FILE *file = pcap_dump_file(dumper);
        if (file) {
            long pos = pcap_dump_ftell(dumper);
            (void)pos;
        }

        pcap_dump_flush(dumper);
        pcap_dump_close(dumper);
    }

    pcap_dumper_t *dumper_append = pcap_dump_open_append(pcap, "./dummy_file");
    if (dumper_append) {
        pcap_dump_close(dumper_append);
    }

    FILE *fp = fopen("./dummy_file", "rb");
    if (fp) {
        pcap_dumper_t *dumper_fopen = pcap_dump_fopen(pcap, fp);
        if (dumper_fopen) {
            pcap_dump_close(dumper_fopen);
        }
        fclose(fp);
    }

    pcap_close(pcap);
    return 0;
}