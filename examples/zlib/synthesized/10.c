// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// compressBound at compress.c:72:15 in zlib.h
// compress at compress.c:63:13 in zlib.h
// uncompress at uncompr.c:82:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Allocate memory for compressed data
    uLongf compressedSize = compressBound(Size);
    Bytef *compressedData = (Bytef *)malloc(compressedSize);
    if (!compressedData) return 0;

    // Compress the input data
    int compressResult = compress(compressedData, &compressedSize, Data, Size);
    if (compressResult != Z_OK) {
        free(compressedData);
        return 0;
    }

    // Allocate memory for decompressed data
    uLongf decompressedSize = Size;
    Bytef *decompressedData = (Bytef *)malloc(decompressedSize);
    if (!decompressedData) {
        free(compressedData);
        return 0;
    }

    // Decompress the compressed data
    int uncompressResult = uncompress(decompressedData, &decompressedSize, compressedData, compressedSize);
    if (uncompressResult != Z_OK) {
        free(compressedData);
        free(decompressedData);
        return 0;
    }

    // Clean up
    free(compressedData);
    free(decompressedData);

    return 0;
}