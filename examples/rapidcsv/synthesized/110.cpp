// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::Load at rapidcsv.h:549:10 in rapidcsv.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "rapidcsv.h"
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_110(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file
    const std::string filePath = "./dummy_file.csv";
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile.is_open()) return 0;

    // Write random data into the CSV file
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        // Test Load with string path
        rapidcsv::Document doc(filePath);
        
        // Test Load with input stream
        std::ifstream inFile(filePath);
        if (inFile.is_open()) {
            rapidcsv::LabelParams labelParams(0, -1);
            rapidcsv::SeparatorParams separatorParams(',', false);
            rapidcsv::ConverterParams converterParams(false, 0.0, 0);
            rapidcsv::LineReaderParams lineReaderParams(false, '#', false);
            doc.Load(inFile, labelParams, separatorParams, converterParams, lineReaderParams);
            inFile.close();
        }
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}