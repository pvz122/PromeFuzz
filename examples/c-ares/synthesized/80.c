// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_dns_class_tostr at ares_dns_mapping.c:236:13 in ares_dns_record.h
// ares_dns_rcode_tostr at ares_dns_mapping.c:902:13 in ares_dns_record.h
// ares_dns_rr_key_datatype at ares_dns_mapping.c:451:21 in ares_dns_record.h
// ares_dns_rr_key_tostr at ares_dns_mapping.c:270:13 in ares_dns_record.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <ares_dns_record.h>

#define CARES_EXTERN extern

int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    ares_dns_rr_key_t key = (ares_dns_rr_key_t)(*Data % 100);
    ares_dns_class_t qclass = (ares_dns_class_t)(*Data % 10);
    ares_dns_rcode_t rcode = (ares_dns_rcode_t)(*Data % 20);

    const char *str = ares_dns_class_tostr(qclass);
    (void)str;

    str = ares_dns_rcode_tostr(rcode);
    (void)str;

    ares_dns_datatype_t datatype = ares_dns_rr_key_datatype(key);
    (void)datatype;

    str = ares_dns_rr_key_tostr(key);
    (void)str;

    return 0;
}