// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_dns_record_create at ares_dns_record.c:52:15 in ares_dns_record.h
// ares_dns_record_rr_add at ares_dns_record.c:396:15 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
// ares_dns_rr_set_str at ares_dns_record.c:1285:15 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
// ares_dns_rr_set_bin at ares_dns_record.c:1231:15 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <ares_dns_record.h>

#define CARES_EXTERN extern

int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    ares_dns_record_t *dnsrec = NULL;
    ares_status_t status = ares_dns_record_create(&dnsrec, 1234, 0, ARES_OPCODE_QUERY, ARES_RCODE_NOERROR);
    if (status != ARES_SUCCESS || !dnsrec) return 0;

    ares_dns_rr_t *rr_out = NULL;
    status = ares_dns_record_rr_add(&rr_out, dnsrec, ARES_SECTION_ANSWER, "example.com", ARES_REC_TYPE_A, ARES_CLASS_IN, 3600);
    if (status != ARES_SUCCESS) {
        ares_dns_record_destroy(dnsrec);
        return 0;
    }

    char *str_val = (char *)malloc(Size + 1);
    if (!str_val) {
        ares_dns_record_destroy(dnsrec);
        return 0;
    }
    memcpy(str_val, Data, Size);
    str_val[Size] = '\0';

    status = ares_dns_rr_set_str(rr_out, ARES_RR_A_ADDR, str_val);
    if (status != ARES_SUCCESS) {
        free(str_val);
        ares_dns_record_destroy(dnsrec);
        return 0;
    }

    status = ares_dns_rr_set_bin(rr_out, ARES_RR_A_ADDR, Data, Size);
    if (status != ARES_SUCCESS) {
        free(str_val);
        ares_dns_record_destroy(dnsrec);
        return 0;
    }

    free(str_val);
    ares_dns_record_destroy(dnsrec);
    return 0;
}