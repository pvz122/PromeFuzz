// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_dns_rec_type_tostr at ares_dns_mapping.c:189:13 in ares_dns_record.h
// ares_dns_rr_key_datatype at ares_dns_mapping.c:451:21 in ares_dns_record.h
// ares_dns_rr_key_to_rec_type at ares_dns_mapping.c:176:21 in ares_dns_record.h
// ares_dns_rr_get_keys at ares_dns_mapping.c:588:32 in ares_dns_record.h
// ares_dns_rr_key_tostr at ares_dns_mapping.c:270:13 in ares_dns_record.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <ares_dns_record.h>
#include <stdint.h>
#include <stdlib.h>

#define CARES_EXTERN extern

int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    // Initialize random values for enums
    int rand_val = *(int *)Data;
    ares_dns_rec_type_t rec_type = (ares_dns_rec_type_t)(rand_val % 256); // Use a reasonable range
    ares_dns_rr_key_t rr_key = (ares_dns_rr_key_t)(rand_val % 1000);

    // Call target functions
    const char *rec_type_str = ares_dns_rec_type_tostr(rec_type);
    (void)rec_type_str;

    ares_dns_datatype_t datatype = ares_dns_rr_key_datatype(rr_key);
    (void)datatype;

    ares_dns_rec_type_t rec_type_from_key = ares_dns_rr_key_to_rec_type(rr_key);
    (void)rec_type_from_key;

    size_t cnt;
    const ares_dns_rr_key_t *keys = ares_dns_rr_get_keys(rec_type, &cnt);
    (void)keys;
    (void)cnt;

    const char *rr_key_str = ares_dns_rr_key_tostr(rr_key);
    (void)rr_key_str;

    return 0;
}