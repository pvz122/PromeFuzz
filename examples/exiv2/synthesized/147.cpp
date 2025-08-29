// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::IptcDataSets::dataSet at datasets.cpp:446:24 in datasets.hpp
// Exiv2::IptcDataSets::dataSetTitle at datasets.cpp:418:27 in datasets.hpp
// Exiv2::IptcDataSets::recordDesc at datasets.cpp:468:27 in datasets.hpp
// Exiv2::IptcDataSets::recordId at datasets.cpp:475:24 in datasets.hpp
// Exiv2::IptcDataSets::dataSetName at datasets.cpp:411:27 in datasets.hpp
// Exiv2::ExifThumb::setJpegThumbnail at exif.cpp:411:17 in exif.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/exiv2.hpp>
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_147(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz Exiv2::IptcDataSets functions
    try {
        // Generate random recordId and dataset number
        uint16_t recordId = (Data[0] << 8) | Data[1 % Size];
        uint16_t datasetNumber = (Data[2 % Size] << 8) | Data[3 % Size];
        std::string datasetName(reinterpret_cast<const char*>(Data), Size);

        // Test dataSet
        Exiv2::IptcDataSets::dataSet(datasetName, recordId);

        // Test dataSetTitle
        Exiv2::IptcDataSets::dataSetTitle(datasetNumber, recordId);

        // Test recordDesc
        Exiv2::IptcDataSets::recordDesc(recordId);

        // Test recordId
        Exiv2::IptcDataSets::recordId(datasetName);

        // Test dataSetName
        Exiv2::IptcDataSets::dataSetName(datasetNumber, recordId);
    } catch (...) {
        // Ignore all exceptions
    }

    // Fuzz Exiv2::ExifThumb::setJpegThumbnail
    try {
        // Write input data to a dummy file
        std::ofstream outFile("./dummy_file", std::ios::binary);
        outFile.write(reinterpret_cast<const char*>(Data), Size);
        outFile.close();

        // Create ExifData and ExifThumb objects
        Exiv2::ExifData exifData;
        Exiv2::ExifThumb thumb(exifData);

        // Test setJpegThumbnail
        Exiv2::URational xres(72, 1);
        Exiv2::URational yres(72, 1);
        thumb.setJpegThumbnail("./dummy_file", xres, yres, 2);
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}