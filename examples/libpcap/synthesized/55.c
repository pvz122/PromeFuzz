// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_init at pcap.c:223:1 in pcap.h
// pcap_open_live at pcap.c:2749:1 in pcap.h
// pcap_set_buffer_size at pcap.c:2625:1 in pcap.h
// pcap_set_snaplen at pcap.c:2535:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_open at pcap.c:4928:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_parsesrcstr at pcap.c:2235:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_55(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap_handle;
    int buffer_size;
    int snaplen;
    int encoding;
    int promisc;
    int timeout;
    int type;
    char host[256], port[256], name[256];
    struct pcap_rmtauth auth = {0};

    memcpy(&buffer_size, Data, sizeof(int));
    memcpy(&snaplen, Data, sizeof(int));
    memcpy(&encoding, Data, sizeof(int));
    memcpy(&promisc, Data, sizeof(int));
    memcpy(&timeout, Data, sizeof(int));
    memcpy(&type, Data, sizeof(int));

    pcap_init(encoding, errbuf);

    pcap_handle = pcap_open_live("any", snaplen, promisc, timeout, errbuf);
    if (pcap_handle) {
        pcap_set_buffer_size(pcap_handle, buffer_size);
        pcap_set_snaplen(pcap_handle, snaplen);
        pcap_close(pcap_handle);
    }

    pcap_handle = pcap_open(NULL, snaplen, promisc, timeout, &auth, errbuf);
    if (pcap_handle) {
        pcap_close(pcap_handle);
    }

    if (Size >= sizeof(int) + 256 * 3) {
        pcap_parsesrcstr((const char *)(Data + sizeof(int)), &type, host, port, name, errbuf);
    }

    return 0;
}