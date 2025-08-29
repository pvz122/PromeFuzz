// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_setLogLevel at logging.c:94:1 in liblouis.h
// lou_registerLogCallback at logging.c:85:1 in liblouis.h
// lou_logEnd at logging.c:161:1 in liblouis.h
// lou_logPrint at logging.c:145:1 in liblouis.h
// lou_logFile at logging.c:128:1 in liblouis.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <liblouis.h>

static void dummy_log_callback(logLevels level, const char *message) {
    // Do nothing
}

int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Set log level
    lou_setLogLevel((logLevels)(Data[0] % 4));

    // Register log callback
    lou_registerLogCallback(dummy_log_callback);

    // Log end (deprecated)
    lou_logEnd();

    // Log print (deprecated)
    char *format = "Test message: %s";
    char *message = "fuzz";
    lou_logPrint(format, message);

    // Log file (deprecated)
    lou_logFile("./dummy_file");

    return 0;
}