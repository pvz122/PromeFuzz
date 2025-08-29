// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetCell at rapidcsv.h:1327:10 in rapidcsv.h
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

extern "C" int LLVMFuzzerTestOneInput_180(const uint8_t *Data, size_t Size) {
    // Prepare dummy CSV file
    std::ofstream outFile("./dummy_file");
    if (!outFile.is_open()) {
        return 0;
    }
    
    // Write random data to the file
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    rapidcsv::Document doc;
    rapidcsv::LabelParams labelParams;
    rapidcsv::SeparatorParams separatorParams;
    rapidcsv::ConverterParams converterParams;
    rapidcsv::LineReaderParams lineReaderParams;

    // Set up parameters
    labelParams.mColumnNameIdx = 0; // Default index
    separatorParams.mSeparator = ','; // Default separator
    converterParams.mHasDefaultConverter = true; // Allow default conversion
    lineReaderParams.mSkipCommentLines = true; // Skip comment lines
    lineReaderParams.mCommentPrefix = '#'; // Default comment prefix

    // Fuzzing: Load the document using both overloads
    try {
        doc.Load("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Handle exceptions
    }

    try {
        std::ifstream inFile("./dummy_file");
        doc.Load(inFile, labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Handle exceptions
    }

    // Fuzzing: Get column name
    for (size_t i = 0; i < 10; ++i) { // Try 10 different indices
        try {
            doc.GetColumnName(i);
        } catch (...) {
            // Handle exceptions
        }
    }

    // Fuzzing: Set cell with random data
    for (size_t i = 0; i < 10; ++i) { // Try 10 different indices
        try {
            doc.SetCell(i, "row_" + std::to_string(i), "test_value");
        } catch (...) {
            // Handle exceptions
        }
    }

    return 0;
}