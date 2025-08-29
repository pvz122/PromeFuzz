// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Converter::ToStr at rapidcsv.h:133:10 in rapidcsv.h
// rapidcsv::Document::SetCell at rapidcsv.h:1345:10 in rapidcsv.h
// rapidcsv::Converter::ToVal at rapidcsv.h:171:10 in rapidcsv.h
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
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_165(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string csvData(reinterpret_cast<const char*>(Data), Size);
    const std::string filePath = "./dummy_file";

    // Write the data to a temporary CSV file
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << csvData;
        outFile.close();
    }

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

    rapidcsv::Document doc;

    try {
        // Fuzzing the Load function with file path
        doc.Load(filePath, labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing the Load function with stream
        std::istringstream stream(csvData);
        doc.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);
        
    } catch (...) {
        // Catch all exceptions
    }

    // Fuzzing the SetCell function
    try {
        std::string columnName = "Column1";
        size_t rowIndex = 0;
        std::string cellData = "TestData";
        doc.SetCell(columnName, rowIndex, cellData);
    } catch (...) {
        // Catch all exceptions
    }

    // Fuzzing Converter ToVal and ToStr
    try {
        rapidcsv::Converter<int> converter(converterParams);
        int value;
        converter.ToVal("123", value);

        std::string outputStr;
        converter.ToStr(value, outputStr);
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}