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
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_155(const uint8_t *Data, size_t Size) {
    // Prepare dummy CSV file
    std::ofstream dummyFile("./dummy_file");
    if (!dummyFile.is_open()) {
        return 0;
    }
    
    // Write fuzz data to the file
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    rapidcsv::Document doc;

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

    // Fuzz Load from file
    try {
        doc.Load("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Handle exceptions
    }

    // Fuzz Load from stream
    std::ifstream stream("./dummy_file");
    if (stream.is_open()) {
        try {
            doc.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);
        } catch (...) {
            // Handle exceptions
        }
        stream.close();
    }

    // Fuzz GetColumnName
    for (size_t i = 0; i < 10; ++i) { // Arbitrarily limit to 10 attempts
        try {
            doc.GetColumnName(i);
        } catch (...) {
            // Handle exceptions
        }
    }

    return 0;
}