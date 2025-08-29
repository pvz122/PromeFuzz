// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
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
#include <iostream>
#include <sstream>
#include <string>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_116(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string inputData(reinterpret_cast<const char*>(Data), Size);
    
    // Create a dummy file for testing
    const std::string dummyFilePath = "./dummy_file";
    std::ofstream dummyFile(dummyFilePath);
    if (dummyFile.is_open()) {
        dummyFile << inputData;
        dummyFile.close();
    }

    try {
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
        rapidcsv::Document docFromFile(dummyFilePath, labelParams, separatorParams, converterParams, lineReaderParams);

        // Test Load from stream
        std::istringstream stream(inputData);
        rapidcsv::Document docFromStream(stream, labelParams, separatorParams, converterParams, lineReaderParams);

        // Test Save functionality
        docFromFile.Save("./output_file.csv");
        docFromStream.Save("./output_stream_file.csv");

    } catch (...) {
        // Catch all exceptions
    }

    // Cleanup: remove dummy file
    std::remove(dummyFilePath.c_str());
    std::remove("./output_file.csv");
    std::remove("./output_stream_file.csv");

    return 0;
}