// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetCell at rapidcsv.h:1345:10 in rapidcsv.h
// rapidcsv::Document::Load at rapidcsv.h:526:10 in rapidcsv.h
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
#include <fstream>
#include <iostream>
#include <string>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_167(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string csvData(reinterpret_cast<const char*>(Data), Size);
    const std::string filePath = "./dummy_file";

    // Write data to a dummy CSV file
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << csvData;
        outFile.close();
    }

    // Initialize parameters
    rapidcsv::LabelParams labelParams;
    labelParams.mColumnNameIdx = 0;

    rapidcsv::SeparatorParams separatorParams;
    separatorParams.mSeparator = ',';
    separatorParams.mTrim = true;

    rapidcsv::ConverterParams converterParams;
    converterParams.mHasDefaultConverter = true;
    converterParams.mDefaultFloat = 0.0;
    converterParams.mDefaultInteger = 0;

    rapidcsv::LineReaderParams lineReaderParams;
    lineReaderParams.mSkipCommentLines = true;
    lineReaderParams.mCommentPrefix = '#';

    // Create Document and load from file
    try {
        rapidcsv::Document doc;
        doc.Load(filePath, labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Load from stream
        std::istringstream stream(csvData);
        rapidcsv::Document docStream(stream, labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Test SetCell
        std::string testColumn = "TestColumn";
        doc.SetCell(testColumn, 0, "TestValue");
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}