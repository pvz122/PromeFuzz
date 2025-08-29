// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_parse_a_reply at ares_parse_a_reply.c:48:5 in ares.h
// ares_parse_ns_reply at ares_parse_ns_reply.c:39:5 in ares.h
// ares_parse_soa_reply at ares_parse_soa_reply.c:30:5 in ares.h
// ares_parse_ptr_reply at ares_parse_ptr_reply.c:186:5 in ares.h
// ares_parse_mx_reply at ares_parse_mx_reply.c:30:5 in ares.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ares.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return 0;
    }

    struct hostent *host = NULL;
    struct ares_addrttl *addrttls = NULL;
    struct ares_soa_reply *soa_out = NULL;
    struct ares_mx_reply *mx_out = NULL;
    int naddrttls = 0;

    // Allocate memory for addrttls
    addrttls = (struct ares_addrttl *)malloc(sizeof(struct ares_addrttl));
    if (!addrttls) {
        return 0;
    }

    // Test ares_parse_a_reply
    ares_parse_a_reply(Data, Size, &host, addrttls, &naddrttls);

    // Test ares_parse_ns_reply
    ares_parse_ns_reply(Data, Size, &host);

    // Test ares_parse_soa_reply
    ares_parse_soa_reply(Data, Size, &soa_out);

    // Test ares_parse_ptr_reply
    struct in_addr addr;
    addr.s_addr = 0x01020304;
    ares_parse_ptr_reply(Data, Size, &addr, sizeof(addr), AF_INET, &host);

    // Test ares_parse_mx_reply
    ares_parse_mx_reply(Data, Size, &mx_out);

    // Cleanup
    if (host) {
        free(host);
    }
    if (addrttls) {
        free(addrttls);
    }
    if (soa_out) {
        free(soa_out->nsname);
        free(soa_out->hostmaster);
        free(soa_out);
    }
    if (mx_out) {
        struct ares_mx_reply *current = mx_out;
        while (current) {
            struct ares_mx_reply *next = current->next;
            free(current->host);
            free(current);
            current = next;
        }
    }

    return 0;
}