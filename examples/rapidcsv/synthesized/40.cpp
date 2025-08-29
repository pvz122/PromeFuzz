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
#include <string>
#include <fstream>
#include <iostream>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    // Prepare a dummy file to use for testing
    const std::string dummyFilePath = "./dummy_file.csv";
    std::ofstream dummyFile(dummyFilePath, std::ios::binary);
    if (!dummyFile) return 0;

    // Write random data to the dummy file
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

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
        // Test Load from file
        rapidcsv::Document docLoad(dummyFilePath, labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Test Load from stream
        std::ifstream stream(dummyFilePath);
        if (stream.is_open()) {
            rapidcsv::Document docStream;
            docStream.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);
        }

        // Test Save
        docLoad.Save(dummyFilePath); // Save back to the same file

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}