// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_inet_ntop at inet_ntop.c:64:20 in ares.h
// ares_dns_pton at ares_hosts_file.c:98:13 in ares_dns_record.h
// ares_dns_rr_get_addr at ares_dns_record.c:748:23 in ares_dns_record.h
// ares_dns_rr_get_addr6 at ares_dns_record.c:765:29 in ares_dns_record.h
// ares_inet_pton at inet_net_pton.c:434:5 in ares.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ares.h"
#include "ares_dns_record.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void fuzz_ares_inet_ntop(const uint8_t *data, size_t size) {
    if (size < 4) return; // Ensure there's enough data for the binary address

    int af = data[0] % 2 == 0 ? AF_INET : AF_INET6;
    char dst[INET6_ADDRSTRLEN];
    ares_socklen_t dst_size = sizeof(dst);

    const void *src = data + 1;
    size_t src_size = af == AF_INET ? 4 : 16; // IPv4: 4 bytes, IPv6: 16 bytes

    if (size - 1 < src_size) return; // Ensure there's enough data for the binary address

    ares_inet_ntop(af, src, dst, dst_size);
}

static void fuzz_ares_dns_pton(const uint8_t *data, size_t size) {
    if (size < 1) return;

    char *ipaddr = (char *)malloc(size + 1);
    if (!ipaddr) return;
    memcpy(ipaddr, data, size);
    ipaddr[size] = '\0';

    struct ares_addr addr;
    addr.family = data[0] % 2 == 0 ? AF_INET : AF_INET6;
    size_t out_len;

    ares_dns_pton(ipaddr, &addr, &out_len);
    free(ipaddr);
}

static void fuzz_ares_dns_rr_get_addr(const uint8_t *data, size_t size) {
    if (size < 1) return;

    ares_dns_rr_t *dns_rr = NULL;
    ares_dns_rr_key_t key = (ares_dns_rr_key_t)(data[0] % 100);

    ares_dns_rr_get_addr(dns_rr, key);
}

static void fuzz_ares_dns_rr_get_addr6(const uint8_t *data, size_t size) {
    if (size < 1) return;

    ares_dns_rr_t *dns_rr = NULL;
    ares_dns_rr_key_t key = (ares_dns_rr_key_t)(data[0] % 100);

    ares_dns_rr_get_addr6(dns_rr, key);
}

static void fuzz_ares_inet_pton(const uint8_t *data, size_t size) {
    if (size < 1) return;

    int af = data[0] % 2 == 0 ? AF_INET : AF_INET6;
    char *src = (char *)malloc(size + 1);
    if (!src) return;
    memcpy(src, data, size);
    src[size] = '\0';

    void *dst = malloc(af == AF_INET ? sizeof(struct in_addr) : sizeof(struct ares_in6_addr));
    if (!dst) {
        free(src);
        return;
    }

    ares_inet_pton(af, src, dst);
    free(src);
    free(dst);
}

int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    switch (data[0] % 5) {
        case 0: fuzz_ares_inet_ntop(data + 1, size - 1); break;
        case 1: fuzz_ares_dns_pton(data + 1, size - 1); break;
        case 2: fuzz_ares_dns_rr_get_addr(data + 1, size - 1); break;
        case 3: fuzz_ares_dns_rr_get_addr6(data + 1, size - 1); break;
        case 4: fuzz_ares_inet_pton(data + 1, size - 1); break;
    }

    return 0;
}