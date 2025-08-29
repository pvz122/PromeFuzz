// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_parse_a_reply at ares_parse_a_reply.c:48:5 in ares.h
// ares_parse_naptr_reply at ares_parse_naptr_reply.c:29:5 in ares.h
// ares_free_data at ares_data.c:46:6 in ares.h
// ares_parse_ptr_reply at ares_parse_ptr_reply.c:186:5 in ares.h
// ares_parse_aaaa_reply at ares_parse_aaaa_reply.c:51:5 in ares.h
// ares_parse_uri_reply at ares_parse_uri_reply.c:30:5 in ares.h
// ares_free_data at ares_data.c:46:6 in ares.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    struct hostent *host = NULL;
    struct ares_addrttl *addrttls = NULL;
    struct ares_addr6ttl *addr6ttls = NULL;
    struct ares_naptr_reply *naptr_out = NULL;
    struct ares_uri_reply *uri_out = NULL;
    int naddrttls = 0;
    int naddr6ttls = 0;

    // Randomly choose which function to fuzz
    int choice = Data[0] % 5;
    Data++;
    Size--;

    switch (choice) {
        case 0:
            ares_parse_a_reply(Data, Size, &host, addrttls, &naddrttls);
            break;
        case 1:
            ares_parse_naptr_reply(Data, Size, &naptr_out);
            if (naptr_out) {
                ares_free_data(naptr_out);
            }
            break;
        case 2: {
            struct in_addr addr;
            memset(&addr, 0, sizeof(addr));
            ares_parse_ptr_reply(Data, Size, &addr, sizeof(addr), AF_INET, &host);
            break;
        }
        case 3:
            ares_parse_aaaa_reply(Data, Size, &host, addr6ttls, &naddr6ttls);
            break;
        case 4:
            ares_parse_uri_reply(Data, Size, &uri_out);
            if (uri_out) {
                ares_free_data(uri_out);
            }
            break;
        default:
            break;
    }

    if (host) {
        free(host);
    }

    return 0;
}