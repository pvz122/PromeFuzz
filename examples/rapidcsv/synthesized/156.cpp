// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::GetColumnName at rapidcsv.h:1361:17 in rapidcsv.h
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

extern "C" int LLVMFuzzerTestOneInput_156(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file
    std::ofstream outFile("./dummy_file");
    if (!outFile.is_open()) {
        return 0;
    }

    // Write fuzzed data to the file
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        // Prepare parameters for Load function
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

        // Test Load from file
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Test Load from stream
        std::ifstream inFile("./dummy_file");
        if (inFile.is_open()) {
            rapidcsv::Document docStream(inFile, labelParams, separatorParams, converterParams, lineReaderParams);
            inFile.close();
        }

        // Test GetColumnName
        for (size_t i = 0; i < 10; ++i) { // Arbitrary limit to avoid out-of-bounds
            doc.GetColumnName(i);
        }
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}