// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetCell at rapidcsv.h:1303:10 in rapidcsv.h
// rapidcsv::Converter::ToStr at rapidcsv.h:133:10 in rapidcsv.h
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
#include <string>
#include <fstream>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string inputData(reinterpret_cast<const char*>(Data), Size);
    
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

    // Write to dummy file
    std::ofstream outFile("./dummy_file");
    if (outFile.is_open()) {
        outFile << inputData;
        outFile.close();
    }

    // Fuzzing the Document::Load function
    try {
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
        doc.Load("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
        std::istringstream stream(inputData);
        doc.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Catch all exceptions
    }

    // Fuzzing the Converter::ToVal and Converter::ToStr functions
    try {
        rapidcsv::Converter<int> converter(converterParams);
        int val;
        std::string str;

        // Fuzzing ToVal
        converter.ToVal(inputData, val);
        
        // Fuzzing ToStr
        converter.ToStr(val, str);
    } catch (...) {
        // Catch all exceptions
    }

    // Fuzzing Document::SetCell
    try {
        rapidcsv::Document doc2("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
        doc2.SetCell("Column1", "Row1", inputData);
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}