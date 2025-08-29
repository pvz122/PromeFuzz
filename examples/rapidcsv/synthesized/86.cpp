// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetCell at rapidcsv.h:1303:10 in rapidcsv.h
// rapidcsv::Converter::ToStr at rapidcsv.h:133:10 in rapidcsv.h
// rapidcsv::Converter::ToVal at rapidcsv.h:171:10 in rapidcsv.h
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

extern "C" int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string input(reinterpret_cast<const char*>(Data), Size);
    
    // Prepare a dummy file
    const std::string filePath = "./dummy_file.csv";
    std::ofstream outFile(filePath);
    if (!outFile) return 0; // File creation failed

    outFile << input; // Write fuzz data to file
    outFile.close();

    // Prepare parameters for Document::Load
    rapidcsv::LabelParams labelParams;
    labelParams.mColumnNameIdx = 0; // Example index

    rapidcsv::SeparatorParams separatorParams;
    separatorParams.mSeparator = ','; // Example separator
    separatorParams.mTrim = true;

    rapidcsv::ConverterParams converterParams;
    converterParams.mHasDefaultConverter = true;
    converterParams.mDefaultFloat = 0.0;
    converterParams.mDefaultInteger = 0;

    rapidcsv::LineReaderParams lineReaderParams;
    lineReaderParams.mSkipCommentLines = true;
    lineReaderParams.mCommentPrefix = '#';

    try {
        // Load the document from the file
        rapidcsv::Document doc(filePath, labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Fuzzing for Load from stream
        std::istringstream stream(input);
        rapidcsv::Document docStream(stream, labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing Converter::ToVal and ToStr
        rapidcsv::Converter<int> converter(converterParams);
        int val;
        std::string str;
        
        converter.ToVal(input, val); // Test ToVal with fuzz input
        converter.ToStr(val, str); // Test ToStr with the converted value

        // Fuzzing SetCell
        doc.SetCell("Column1", "Row1", val); // Update a cell with fuzzed int value

    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}