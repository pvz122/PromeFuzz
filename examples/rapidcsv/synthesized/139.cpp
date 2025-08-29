// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::Load at rapidcsv.h:526:10 in rapidcsv.h
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
#include <string>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_139(const uint8_t *Data, size_t Size) {
    // Prepare dummy CSV file
    const std::string filepath = "./dummy_file.csv";
    std::ofstream outFile(filepath);
    if (!outFile.is_open()) return 0;

    // Write random data to the file
    for (size_t i = 0; i < Size; ++i) {
        outFile << static_cast<char>(Data[i]);
        if (i % 10 == 9) outFile << "\n"; // New line every 10 characters
    }
    outFile.close();

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
        // Load from file
        rapidcsv::Document doc;
        doc.Load(filepath, labelParams, separatorParams, converterParams, lineReaderParams);

        // Load from stream
        std::ifstream inFile(filepath);
        if (inFile.is_open()) {
            rapidcsv::Document docStream(inFile, labelParams, separatorParams, converterParams, lineReaderParams);
        }
    } catch (...) {
        // Catch any exceptions thrown by rapidcsv
    }

    // Save the document back to a file
    try {
        rapidcsv::Document doc;
        doc.Save(filepath);
    } catch (...) {
        // Catch any exceptions thrown by rapidcsv
    }

    return 0;
}