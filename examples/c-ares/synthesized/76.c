// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_dns_rr_get_u16 at ares_dns_record.c:799:16 in ares_dns_record.h
// ares_dns_opt_get_datatype at ares_dns_mapping.c:815:25 in ares_dns_record.h
// ares_dns_rr_get_opt at ares_dns_record.c:1007:16 in ares_dns_record.h
// ares_dns_rr_get_opt_cnt at ares_dns_record.c:990:8 in ares_dns_record.h
// ares_dns_rr_get_opt_byid at ares_dns_record.c:1045:13 in ares_dns_record.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <ares_dns_record.h>

int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void *)) {
        return 0;
    }

    ares_dns_rr_t *dns_rr = (ares_dns_rr_t *)Data;
    ares_dns_rr_key_t key = (ares_dns_rr_key_t)(*Data);
    unsigned short opt = (unsigned short)(*(Data + 1));
    size_t idx = (size_t)(*(Data + 2));
    const unsigned char *val = NULL;
    size_t val_len = 0;

    // Fuzz ares_dns_rr_get_u16
    ares_dns_rr_get_u16(dns_rr, key);

    // Fuzz ares_dns_opt_get_datatype
    ares_dns_opt_get_datatype(key, opt);

    // Fuzz ares_dns_rr_get_opt
    ares_dns_rr_get_opt(dns_rr, key, idx, &val, &val_len);

    // Fuzz ares_dns_rr_get_opt_cnt
    ares_dns_rr_get_opt_cnt(dns_rr, key);

    // Fuzz ares_dns_rr_get_opt_byid
    ares_dns_rr_get_opt_byid(dns_rr, key, opt, &val, &val_len);

    return 0;
}