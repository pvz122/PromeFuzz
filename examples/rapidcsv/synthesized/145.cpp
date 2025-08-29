// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
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
#include "rapidcsv.h"
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_145(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string inputData(reinterpret_cast<const char*>(Data), Size);
    const char* dummyFilePath = "./dummy_file";

    // Write input data to a dummy file
    std::ofstream dummyFile(dummyFilePath);
    if (dummyFile.is_open()) {
        dummyFile << inputData;
        dummyFile.close();
    }

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

    // Fuzzing Load function with file path
    try {
        rapidcsv::Document doc;
        doc.Load(dummyFilePath, labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Catch exceptions for the first overload
    }

    // Fuzzing Load function with stream
    try {
        std::istringstream stream(inputData);
        rapidcsv::Document doc(stream, labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Catch exceptions for the second overload
    }

    // Cleanup: remove the dummy file
    std::remove(dummyFilePath);

    return 0;
}