// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::Load at rapidcsv.h:526:10 in rapidcsv.h
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
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <rapidcsv.h>

extern "C" int LLVMFuzzerTestOneInput_135(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string inputData(reinterpret_cast<const char*>(Data), Size);
    const std::string filePath = "./dummy_file";

    // Write the input data to a dummy CSV file
    std::ofstream outFile(filePath);
    outFile << inputData;
    outFile.close();

    // Prepare parameters
    rapidcsv::LabelParams labelParams(0, -1);
    rapidcsv::SeparatorParams separatorParams(',', false);
    rapidcsv::ConverterParams converterParams(false, 0.0, 0);
    rapidcsv::LineReaderParams lineReaderParams(false, '#', false);

    // Fuzz the Load function with file path
    try {
        rapidcsv::Document doc;
        doc.Load(filePath, labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Catch exceptions from Load with file path
    }

    // Fuzz the Load function with stream
    try {
        std::istringstream stream(inputData);
        rapidcsv::Document doc;
        doc.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Catch exceptions from Load with stream
    }

    return 0;
}