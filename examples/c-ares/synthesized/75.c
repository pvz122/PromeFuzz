// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_dns_record_create at ares_dns_record.c:52:15 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
// ares_dns_record_query_add at ares_dns_record.c:252:15 in ares_dns_record.h
// ares_dns_rr_get_class at ares_dns_record.c:521:18 in ares_dns_record.h
// ares_dns_class_tostr at ares_dns_mapping.c:236:13 in ares_dns_record.h
// ares_dns_class_fromstr at ares_dns_mapping.c:663:13 in ares_dns_record.h
// ares_dns_rec_type_fromstr at ares_dns_mapping.c:692:13 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <ares_dns_record.h>

#define CARES_EXTERN extern

int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    ares_dns_record_t *dnsrec;
    ares_status_t status = ares_dns_record_create(&dnsrec, 0, 0, ARES_OPCODE_QUERY, ARES_RCODE_NOERROR);
    if (status != ARES_SUCCESS) {
        return 0;
    }

    // Generate a null-terminated string from the input data
    char *name = (char *)malloc(Size + 1);
    if (!name) {
        ares_dns_record_destroy(dnsrec);
        return 0;
    }
    memcpy(name, Data, Size);
    name[Size] = '\0';

    // Fuzz ares_dns_record_query_add
    ares_dns_record_query_add(dnsrec, name, ARES_REC_TYPE_A, ARES_CLASS_IN);

    // Fuzz ares_dns_rr_get_class
    ares_dns_rr_t *rr = NULL;
    ares_dns_rr_get_class(rr);

    // Fuzz ares_dns_class_tostr
    ares_dns_class_tostr(ARES_CLASS_IN);

    // Fuzz ares_dns_class_fromstr
    ares_dns_class_t qclass;
    ares_dns_class_fromstr(&qclass, name);

    // Fuzz ares_dns_rec_type_fromstr
    ares_dns_rec_type_t qtype;
    ares_dns_rec_type_fromstr(&qtype, name);

    free(name);
    ares_dns_record_destroy(dnsrec);

    return 0;
}