// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_dns_class_tostr at ares_dns_mapping.c:236:13 in ares_dns_record.h
// ares_dns_rec_type_tostr at ares_dns_mapping.c:189:13 in ares_dns_record.h
// ares_dns_section_tostr at ares_dns_mapping.c:737:13 in ares_dns_record.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ares.h"
#include "ares_dns_record.h"

int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size < 3) {
        return 0;
    }

    ares_dns_class_t qclass = (ares_dns_class_t)Data[0];
    ares_dns_rec_type_t type = (ares_dns_rec_type_t)Data[1];
    ares_dns_section_t section = (ares_dns_section_t)Data[2];

    const char *class_str = ares_dns_class_tostr(qclass);
    const char *type_str = ares_dns_rec_type_tostr(type);
    const char *section_str = ares_dns_section_tostr(section);

    (void)class_str;
    (void)type_str;
    (void)section_str;

    return 0;
}