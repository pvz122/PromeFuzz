// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_parse_a_reply at ares_parse_a_reply.c:48:5 in ares.h
// ares_free_hostent at ares_free_hostent.c:33:6 in ares.h
// ares_parse_ns_reply at ares_parse_ns_reply.c:39:5 in ares.h
// ares_free_hostent at ares_free_hostent.c:33:6 in ares.h
// ares_parse_soa_reply at ares_parse_soa_reply.c:30:5 in ares.h
// ares_parse_ptr_reply at ares_parse_ptr_reply.c:186:5 in ares.h
// ares_free_hostent at ares_free_hostent.c:33:6 in ares.h
// ares_parse_srv_reply at ares_parse_srv_reply.c:30:5 in ares.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_55(const uint8_t *Data, size_t Size) {
    struct hostent *host = NULL;
    struct ares_addrttl *addrttls = NULL;
    int naddrttls = 0;
    struct ares_soa_reply *soa_out = NULL;
    struct ares_srv_reply *srv_out = NULL;

    // Fuzz ares_parse_a_reply
    ares_parse_a_reply(Data, Size, &host, addrttls, &naddrttls);
    if (host) {
        ares_free_hostent(host);
    }

    // Fuzz ares_parse_ns_reply
    ares_parse_ns_reply(Data, Size, &host);
    if (host) {
        ares_free_hostent(host);
    }

    // Fuzz ares_parse_soa_reply
    ares_parse_soa_reply(Data, Size, &soa_out);
    if (soa_out) {
        free(soa_out->nsname);
        free(soa_out->hostmaster);
        free(soa_out);
    }

    // Fuzz ares_parse_ptr_reply
    struct in_addr addr;
    memset(&addr, 0, sizeof(addr));
    ares_parse_ptr_reply(Data, Size, &addr, sizeof(addr), AF_INET, &host);
    if (host) {
        ares_free_hostent(host);
    }

    // Fuzz ares_parse_srv_reply
    ares_parse_srv_reply(Data, Size, &srv_out);
    while (srv_out) {
        struct ares_srv_reply *next = srv_out->next;
        free(srv_out->host);
        free(srv_out);
        srv_out = next;
    }

    return 0;
}