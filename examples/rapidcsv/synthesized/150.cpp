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
#include <string>
#include <vector>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_150(const uint8_t *Data, size_t Size) {
    // Prepare input data for CSV file
    std::string csvData(reinterpret_cast<const char*>(Data), Size);
    std::ofstream outFile("./dummy_file");
    if (outFile.is_open()) {
        outFile << csvData;
        outFile.close();
    }

    // Initialize parameters for Load function
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

    try {
        // Test the Load function with file
        rapidcsv::Document doc;
        doc.Load("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);

        // Test the Load function with stream
        std::istringstream stream(csvData);
        doc.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);

        // Test GetColumnName with various indices
        for (size_t i = 0; i < 10; ++i) {
            doc.GetColumnName(i);
        }
    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}