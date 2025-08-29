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
#include <fstream>
#include <iostream>
#include <string>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_146(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string csvData(reinterpret_cast<const char*>(Data), Size);
    const std::string dummyFilePath = "./dummy_file";

    // Write the CSV data to a dummy file
    std::ofstream outFile(dummyFilePath);
    outFile << csvData;
    outFile.close();

    // Create instances of parameters
    rapidcsv::LabelParams labelParams(0, -1);
    rapidcsv::SeparatorParams separatorParams(',', false);
    rapidcsv::ConverterParams converterParams(false, 0.0, 0);
    rapidcsv::LineReaderParams lineReaderParams(false, '#', false);

    try {
        // Test Load from file
        rapidcsv::Document docFile;
        docFile.Load(dummyFilePath, labelParams, separatorParams, converterParams, lineReaderParams);

        // Test Load from stream
        std::istringstream stream(csvData);
        rapidcsv::Document docStream;
        docStream.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}