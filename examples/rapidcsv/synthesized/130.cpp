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
#include "rapidcsv.h"
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_130(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file to test
    std::string filePath = "./dummy_file";
    std::ofstream outFile(filePath, std::ios::binary);
    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<const char*>(Data), Size);
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

    // Create Document and load CSV file
    try {
        rapidcsv::Document doc(filePath, labelParams, separatorParams, converterParams, lineReaderParams);
        doc.Load(filePath, labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Test the second overload with the file stream
        std::ifstream inFile(filePath);
        if (inFile.is_open()) {
            doc.Load(inFile, labelParams, separatorParams, converterParams, lineReaderParams);
            inFile.close();
        }

        // Save the document to a new file
        doc.Save("./output_file");

    } catch (...) {
        // Catch any exceptions thrown by rapidcsv
    }

    return 0;
}