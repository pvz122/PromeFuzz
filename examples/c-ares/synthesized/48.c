// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_dns_record_create at ares_dns_record.c:52:15 in ares_dns_record.h
// ares_dns_record_rr_add at ares_dns_record.c:396:15 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
// ares_dns_rr_set_u8 at ares_dns_record.c:1131:15 in ares_dns_record.h
// ares_dns_rr_set_u16 at ares_dns_record.c:1149:15 in ares_dns_record.h
// ares_dns_rr_set_u32 at ares_dns_record.c:1167:15 in ares_dns_record.h
// ares_dns_rr_set_opt at ares_dns_record.c:1395:15 in ares_dns_record.h
// ares_dns_rr_set_bin at ares_dns_record.c:1231:15 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <ares_dns_record.h>

#define CARES_EXTERN extern

int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    ares_dns_record_t *dns_record;
    ares_status_t status = ares_dns_record_create(&dns_record, 0, 0, ARES_OPCODE_QUERY, ARES_RCODE_NOERROR);
    if (status != ARES_SUCCESS) {
        return 0;
    }

    ares_dns_rr_t *dns_rr;
    status = ares_dns_record_rr_add(&dns_rr, dns_record, ARES_SECTION_ANSWER, "example.com", ARES_REC_TYPE_A, ARES_CLASS_IN, 0);
    if (status != ARES_SUCCESS) {
        ares_dns_record_destroy(dns_record);
        return 0;
    }

    // Fuzz ares_dns_rr_set_u8
    ares_dns_rr_set_u8(dns_rr, ARES_RR_A_ADDR, (unsigned char)Data[0]);

    // Fuzz ares_dns_rr_set_u16
    unsigned short u16_val = 0;
    if (Size >= 2) {
        memcpy(&u16_val, Data, sizeof(u16_val));
    }
    ares_dns_rr_set_u16(dns_rr, ARES_RR_A_ADDR, u16_val);

    // Fuzz ares_dns_rr_set_u32
    unsigned int u32_val = 0;
    if (Size >= 4) {
        memcpy(&u32_val, Data, sizeof(u32_val));
    }
    ares_dns_rr_set_u32(dns_rr, ARES_RR_A_ADDR, u32_val);

    // Fuzz ares_dns_rr_set_opt
    ares_dns_rr_set_opt(dns_rr, ARES_RR_A_ADDR, 0, Data, Size);

    // Fuzz ares_dns_rr_set_bin
    ares_dns_rr_set_bin(dns_rr, ARES_RR_A_ADDR, Data, Size);

    ares_dns_record_destroy(dns_record);

    return 0;
}