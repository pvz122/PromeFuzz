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
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_182(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string csvData(reinterpret_cast<const char*>(Data), Size);
    std::ofstream outFile("./dummy_file");
    outFile << csvData;
    outFile.close();

    rapidcsv::Document doc;

    // Prepare parameters
    rapidcsv::LabelParams labelParams;
    labelParams.mColumnNameIdx = 0; // Example index

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

    // Fuzz testing Load function with file path
    try {
        doc.Load("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Handle exceptions silently
    }

    // Fuzz testing Load function with stream
    std::istringstream stream(csvData);
    try {
        doc.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Handle exceptions silently
    }

    // Fuzz testing GetColumnName
    try {
        for (size_t i = 0; i < 10; ++i) { // Attempt to access first 10 column names
            doc.GetColumnName(i);
        }
    } catch (...) {
        // Handle exceptions silently
    }

    // Fuzz testing SetCell
    try {
        doc.SetCell<std::string>(0, "Row1", "TestValue");
    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}