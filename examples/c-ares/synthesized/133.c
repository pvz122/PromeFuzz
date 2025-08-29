// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_dns_record_create at ares_dns_record.c:52:15 in ares_dns_record.h
// ares_dns_record_rr_add at ares_dns_record.c:396:15 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
// ares_dns_rr_get_str at ares_dns_record.c:972:13 in ares_dns_record.h
// ares_dns_rr_get_u8 at ares_dns_record.c:782:15 in ares_dns_record.h
// ares_dns_rr_get_u16 at ares_dns_record.c:799:16 in ares_dns_record.h
// ares_dns_rr_get_bin at ares_dns_record.c:833:22 in ares_dns_record.h
// ares_dns_rr_get_opt_cnt at ares_dns_record.c:990:8 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ares.h"
#include "ares_dns_record.h"

int LLVMFuzzerTestOneInput_133(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    ares_dns_record_t *dns_record;
    ares_status_t status = ares_dns_record_create(&dns_record, 0, 0, ARES_OPCODE_QUERY, ARES_RCODE_NOERROR);
    if (status != ARES_SUCCESS) {
        return 0;
    }

    ares_dns_rr_t *dns_rr = NULL;
    status = ares_dns_record_rr_add(&dns_rr, dns_record, ARES_SECTION_ANSWER, "example.com", ARES_REC_TYPE_A, ARES_CLASS_IN, 0);
    if (status != ARES_SUCCESS || !dns_rr) {
        ares_dns_record_destroy(dns_record);
        return 0;
    }

    ares_dns_rr_key_t key = (ares_dns_rr_key_t)(Data[0] % 100);

    // Fuzz ares_dns_rr_get_str
    const char *str = ares_dns_rr_get_str(dns_rr, key);

    // Fuzz ares_dns_rr_get_u8
    unsigned char u8 = ares_dns_rr_get_u8(dns_rr, key);

    // Fuzz ares_dns_rr_get_u16
    unsigned short u16 = ares_dns_rr_get_u16(dns_rr, key);

    // Fuzz ares_dns_rr_get_bin
    size_t len;
    const unsigned char *bin = ares_dns_rr_get_bin(dns_rr, key, &len);

    // Fuzz ares_dns_rr_get_opt_cnt
    size_t opt_cnt = ares_dns_rr_get_opt_cnt(dns_rr, key);

    ares_dns_record_destroy(dns_record);

    return 0;
}