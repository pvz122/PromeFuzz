// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_inet_pton at inet_net_pton.c:434:5 in ares.h
// ares_dns_record_create at ares_dns_record.c:52:15 in ares_dns_record.h
// ares_dns_record_rr_add at ares_dns_record.c:396:15 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
// ares_dns_rr_set_addr at ares_dns_record.c:1094:15 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <ares_dns_record.h>
#include <arpa/inet.h>

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct in_addr)) {
        return 0;
    }

    struct in_addr addr;
    char src[INET_ADDRSTRLEN];
    memcpy(&addr, Data, sizeof(struct in_addr));
    inet_ntop(AF_INET, &addr, src, INET_ADDRSTRLEN);

    int result = ares_inet_pton(AF_INET, src, &addr);
    if (result != 1) {
        return 0;
    }

    ares_dns_record_t *dnsrec;
    ares_status_t status = ares_dns_record_create(&dnsrec, 0, 0, ARES_OPCODE_QUERY, ARES_RCODE_NOERROR);
    if (status != ARES_SUCCESS) {
        return 0;
    }

    ares_dns_rr_t *rr_out = NULL;
    status = ares_dns_record_rr_add(&rr_out, dnsrec, ARES_SECTION_ANSWER, "example.com", ARES_REC_TYPE_A, ARES_CLASS_IN, 3600);
    if (status != ARES_SUCCESS) {
        ares_dns_record_destroy(dnsrec);
        return 0;
    }

    status = ares_dns_rr_set_addr(rr_out, ARES_RR_A_ADDR, &addr);
    if (status != ARES_SUCCESS) {
        ares_dns_record_destroy(dnsrec);
        return 0;
    }

    ares_dns_record_destroy(dnsrec);
    return 0;
}