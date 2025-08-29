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
#include <ares.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>

int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    struct hostent *host = NULL;
    struct ares_addrttl *addrttls = NULL;
    struct ares_soa_reply *soa_out = NULL;
    struct ares_mx_reply *mx_out = NULL;
    int naddrttls = 0;

    // Randomly choose which function to fuzz
    switch (Data[0] % 5) {
        case 0:
            ares_parse_a_reply(Data + 1, Size - 1, &host, addrttls, &naddrttls);
            break;
        case 1:
            ares_parse_ns_reply(Data + 1, Size - 1, &host);
            break;
        case 2:
            ares_parse_soa_reply(Data + 1, Size - 1, &soa_out);
            if (soa_out) {
                free(soa_out->nsname);
                free(soa_out->hostmaster);
                free(soa_out);
            }
            break;
        case 3: {
            struct in_addr addr;
            memset(&addr, 0, sizeof(addr));
            ares_parse_ptr_reply(Data + 1, Size - 1, &addr, sizeof(addr), AF_INET, &host);
            break;
        }
        case 4:
            ares_parse_mx_reply(Data + 1, Size - 1, &mx_out);
            while (mx_out) {
                struct ares_mx_reply *next = mx_out->next;
                free(mx_out->host);
                free(mx_out);
                mx_out = next;
            }
            break;
    }

    if (host) {
        free(host->h_name);
        for (int i = 0; host->h_aliases[i]; i++) {
            free(host->h_aliases[i]);
        }
        free(host->h_aliases);
        free(host->h_addr_list);
        free(host);
    }

    return 0;
}