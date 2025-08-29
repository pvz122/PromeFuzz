// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::GetColumnName at rapidcsv.h:1361:17 in rapidcsv.h
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

extern "C" int LLVMFuzzerTestOneInput_160(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file
    std::string dummyFilePath = "./dummy_file";
    std::ofstream dummyFile(dummyFilePath, std::ios::binary);
    if (!dummyFile) {
        return 0;
    }
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    // Initialize parameters
    rapidcsv::LabelParams labelParams(0);
    rapidcsv::SeparatorParams separatorParams(',', true);
    rapidcsv::ConverterParams converterParams(true, 0.0, 0);
    rapidcsv::LineReaderParams lineReaderParams(true, '#');

    try {
        // Test Document Load from file
        rapidcsv::Document doc(dummyFilePath, labelParams, separatorParams, converterParams, lineReaderParams);
        doc.Load(dummyFilePath, labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Test Document Load from stream
        std::ifstream stream(dummyFilePath);
        if (stream.is_open()) {
            rapidcsv::Document docStream;
            docStream.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);
            stream.close();
        }

        // Test GetColumnName
        for (size_t i = 0; i < 10; ++i) { // Arbitrary upper limit for column index
            doc.GetColumnName(i);
        }
    } catch (...) {
        // Catch all exceptions
    }

    // Cleanup
    std::remove(dummyFilePath.c_str());
    
    return 0;
}