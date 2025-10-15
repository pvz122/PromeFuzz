// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_live at pcap.c:2749:1 in pcap.h
// pcap_activate at pcap.c:2695:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_dispatch at pcap.c:2893:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_datalink at pcap.c:2938:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_fileno at pcap.c:3501:1 in pcap.h
// pcap_close at pcap.c:4156:1 in pcap.h
// pcap_get_selectable_fd at pcap.c:3509:1 in pcap.h
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
#include <string.h>

static void dummy_callback(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    // Do nothing
}

int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap_handle = pcap_open_live("any", 65535, 1, 1000, errbuf);
    if (pcap_handle == NULL) return 0;

    int activate_result = pcap_activate(pcap_handle);
    if (activate_result < 0) {
        pcap_close(pcap_handle);
        return 0;
    }

    int dispatch_result = pcap_dispatch(pcap_handle, 1, dummy_callback, NULL);
    if (dispatch_result < 0) {
        pcap_close(pcap_handle);
        return 0;
    }

    int datalink_result = pcap_datalink(pcap_handle);
    if (datalink_result < 0) {
        pcap_close(pcap_handle);
        return 0;
    }

    int fileno_result = pcap_fileno(pcap_handle);
    if (fileno_result < 0) {
        pcap_close(pcap_handle);
        return 0;
    }

    int selectable_fd_result = pcap_get_selectable_fd(pcap_handle);
    if (selectable_fd_result < 0) {
        pcap_close(pcap_handle);
        return 0;
    }

    pcap_close(pcap_handle);
    return 0;
}