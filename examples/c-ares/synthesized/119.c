// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_dns_record_create at ares_dns_record.c:52:15 in ares_dns_record.h
// ares_dns_record_rr_cnt at ares_dns_record.c:349:8 in ares_dns_record.h
// ares_dns_record_rr_cnt at ares_dns_record.c:349:8 in ares_dns_record.h
// ares_dns_record_rr_cnt at ares_dns_record.c:349:8 in ares_dns_record.h
// ares_dns_record_get_id at ares_dns_record.c:92:16 in ares_dns_record.h
// ares_dns_record_get_flags at ares_dns_record.c:109:16 in ares_dns_record.h
// ares_dns_record_get_rcode at ares_dns_record.c:125:18 in ares_dns_record.h
// ares_dns_record_get_opcode at ares_dns_record.c:117:19 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ares.h"
#include "ares_dns_record.h"

#define CARES_EXTERN extern

int LLVMFuzzerTestOneInput_119(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    ares_dns_record_t *dnsrec = NULL;
    ares_dns_record_create(&dnsrec, 0, 0, ARES_OPCODE_QUERY, ARES_RCODE_NOERROR);

    if (dnsrec == NULL) {
        return 0;
    }

    // Fuzz ares_dns_record_rr_cnt
    ares_dns_record_rr_cnt(dnsrec, ARES_SECTION_ANSWER);
    ares_dns_record_rr_cnt(dnsrec, ARES_SECTION_AUTHORITY);
    ares_dns_record_rr_cnt(dnsrec, ARES_SECTION_ADDITIONAL);

    // Fuzz ares_dns_record_get_id
    ares_dns_record_get_id(dnsrec);

    // Fuzz ares_dns_record_get_flags
    ares_dns_record_get_flags(dnsrec);

    // Fuzz ares_dns_record_get_rcode
    ares_dns_record_get_rcode(dnsrec);

    // Fuzz ares_dns_record_get_opcode
    ares_dns_record_get_opcode(dnsrec);

    ares_dns_record_destroy(dnsrec);

    return 0;
}