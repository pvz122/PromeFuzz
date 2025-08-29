// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_dns_record_create at ares_dns_record.c:52:15 in ares_dns_record.h
// ares_dns_record_rr_del at ares_dns_record.c:450:15 in ares_dns_record.h
// ares_dns_record_rr_get at ares_dns_record.c:474:16 in ares_dns_record.h
// ares_dns_rr_get_name at ares_dns_record.c:505:13 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ares.h"
#include "ares_dns_record.h"

#define CARES_EXTERN extern

int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t) * 2)
        return 0;

    size_t sect = *(size_t *)Data;
    size_t idx = *(size_t *)(Data + sizeof(size_t));

    ares_dns_record_t *dnsrec = NULL;
    ares_status_t status = ares_dns_record_create(&dnsrec, 0, 0, ARES_OPCODE_QUERY, ARES_RCODE_NOERROR);
    if (status != ARES_SUCCESS || !dnsrec)
        return 0;

    status = ares_dns_record_rr_del(dnsrec, (ares_dns_section_t)sect, idx);
    if (status == ARES_SUCCESS) {
        ares_dns_rr_t *rr = ares_dns_record_rr_get(dnsrec, (ares_dns_section_t)sect, idx);
        if (rr) {
            const char *name = ares_dns_rr_get_name(rr);
            (void)name; // Avoid unused variable warning
        }
    }

    ares_dns_record_destroy(dnsrec);
    return 0;
}