// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_dns_record_create at ares_dns_record.c:52:15 in ares_dns_record.h
// ares_dns_record_query_cnt at ares_dns_record.c:244:8 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
// ares_dns_record_query_set_name at ares_dns_record.c:283:15 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
// ares_dns_record_query_set_type at ares_dns_record.c:306:15 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
// ares_dns_record_destroy at ares_dns_record.c:223:6 in ares_dns_record.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <ares_dns_record.h>

int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    ares_dns_record_t *dnsrec;
    ares_status_t status = ares_dns_record_create(&dnsrec, 0, 0, ARES_OPCODE_QUERY, ARES_RCODE_NOERROR);
    if (status != ARES_SUCCESS || !dnsrec) {
        return 0;
    }

    size_t query_cnt = ares_dns_record_query_cnt(dnsrec);
    if (query_cnt == 0) {
        ares_dns_record_destroy(dnsrec);
        return 0;
    }

    char *name = (char *)malloc(Size + 1);
    if (!name) {
        ares_dns_record_destroy(dnsrec);
        return 0;
    }
    memcpy(name, Data, Size);
    name[Size] = '\0';

    status = ares_dns_record_query_set_name(dnsrec, 0, name);
    if (status != ARES_SUCCESS) {
        free(name);
        ares_dns_record_destroy(dnsrec);
        return 0;
    }

    ares_dns_rec_type_t qtype = (ares_dns_rec_type_t)(Data[0] % 256);
    status = ares_dns_record_query_set_type(dnsrec, 0, qtype);
    if (status != ARES_SUCCESS) {
        free(name);
        ares_dns_record_destroy(dnsrec);
        return 0;
    }

    free(name);
    ares_dns_record_destroy(dnsrec);
    return 0;
}