// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_parse_a_reply at ares_parse_a_reply.c:48:5 in ares.h
// ares_parse_naptr_reply at ares_parse_naptr_reply.c:29:5 in ares.h
// ares_free_data at ares_data.c:46:6 in ares.h
// ares_parse_soa_reply at ares_parse_soa_reply.c:30:5 in ares.h
// ares_free_data at ares_data.c:46:6 in ares.h
// ares_parse_aaaa_reply at ares_parse_aaaa_reply.c:51:5 in ares.h
// ares_parse_srv_reply at ares_parse_srv_reply.c:30:5 in ares.h
// ares_free_data at ares_data.c:46:6 in ares.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_91(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    struct hostent *host = NULL;
    struct ares_addrttl *addrttls = NULL;
    struct ares_addr6ttl *addr6ttls = NULL;
    struct ares_naptr_reply *naptr_out = NULL;
    struct ares_soa_reply *soa_out = NULL;
    struct ares_srv_reply *srv_out = NULL;
    int naddrttls = 0;

    // Randomly choose which function to fuzz
    int choice = Data[0] % 5;
    switch (choice) {
        case 0:
            ares_parse_a_reply(Data, Size, &host, addrttls, &naddrttls);
            break;
        case 1:
            ares_parse_naptr_reply(Data, Size, &naptr_out);
            if (naptr_out) ares_free_data(naptr_out);
            break;
        case 2:
            ares_parse_soa_reply(Data, Size, &soa_out);
            if (soa_out) ares_free_data(soa_out);
            break;
        case 3:
            ares_parse_aaaa_reply(Data, Size, &host, addr6ttls, &naddrttls);
            break;
        case 4:
            ares_parse_srv_reply(Data, Size, &srv_out);
            if (srv_out) ares_free_data(srv_out);
            break;
    }

    if (host) free(host);
    if (addrttls) free(addrttls);
    if (addr6ttls) free(addr6ttls);

    return 0;
}