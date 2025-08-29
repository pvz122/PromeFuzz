// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
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
#include <iostream>
#include <fstream>
#include <string>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_101(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string inputData(reinterpret_cast<const char*>(Data), Size);
    
    // Prepare dummy CSV file
    std::ofstream dummyFile("./dummy_file");
    if (dummyFile.is_open()) {
        dummyFile << inputData;
        dummyFile.close();
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

    try {
        // Load document from dummy file
        rapidcsv::Document docLoad("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Save document to the same or different path
        docLoad.Save("./dummy_file");

        // Load from stream
        std::istringstream stream(inputData);
        rapidcsv::Document docStream;
        docStream.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);
        
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}