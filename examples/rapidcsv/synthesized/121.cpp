// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::Load at rapidcsv.h:526:10 in rapidcsv.h
// rapidcsv::Document::Load at rapidcsv.h:549:10 in rapidcsv.h
// rapidcsv::Document::Save at rapidcsv.h:569:10 in rapidcsv.h
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
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *Data, size_t Size) {
    // Prepare dummy CSV file
    std::ofstream dummyFile("./dummy_file");
    if (!dummyFile.is_open()) return 0;

    // Write random data to the dummy file
    for (size_t i = 0; i < Size; ++i) {
        dummyFile << static_cast<char>(Data[i]);
        if (i % 10 == 9) dummyFile << "\n"; // New line every 10 characters
    }
    dummyFile.close();

    rapidcsv::Document doc;

    // Prepare parameters
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
        // Catch all exceptions
    }

    // Fuzz Load from stream
    std::ifstream inputStream("./dummy_file");
    if (inputStream.is_open()) {
        try {
            doc.Load(inputStream, labelParams, separatorParams, converterParams, lineReaderParams);
        } catch (...) {
            // Catch all exceptions
        }
        inputStream.close();
    }

    // Fuzz Save
    try {
        doc.Save("./output_file");
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}