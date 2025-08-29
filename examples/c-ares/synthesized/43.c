// This fuzz driver is generated for library cares, aiming to fuzz the following functions:
// ares_create_query at ares_create_query.c:66:5 in ares.h
// ares_free_string at ares_free_string.c:30:6 in ares.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ares.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Ensure the input data is null-terminated
    char *name = malloc(Size + 1);
    if (!name) return 0;
    memcpy(name, Data, Size);
    name[Size] = '\0';

    // Initialize variables
    int dnsclass = 1; // IN class
    int type = 1;     // A type
    unsigned short id = 1234;
    int rd = 1;       // Recursion desired
    unsigned char *buf = NULL;
    int buflen = 0;
    int max_udp_size = 512;

    // Create query
    int status = ares_create_query(name, dnsclass, type, id, rd, &buf, &buflen, max_udp_size);

    // Free the allocated buffer if the query was successful
    if (status == ARES_SUCCESS && buf != NULL) {
        ares_free_string(buf);
    }

    // Free the allocated name
    free(name);

    return 0;
}