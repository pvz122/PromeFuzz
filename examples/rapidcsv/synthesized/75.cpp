// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetCell at rapidcsv.h:1303:10 in rapidcsv.h
// rapidcsv::Converter::ToStr at rapidcsv.h:133:10 in rapidcsv.h
// rapidcsv::Converter::ToVal at rapidcsv.h:171:10 in rapidcsv.h
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
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size) {
    // Prepare input string from fuzz data
    std::string inputData(reinterpret_cast<const char*>(Data), Size);
    
    // Create dummy CSV file
    std::ofstream dummyFile("./dummy_file");
    if (dummyFile.is_open()) {
        dummyFile << inputData;
        dummyFile.close();
    }

    try {
        // Prepare parameters for Document Load
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

        // Load document from file
        rapidcsv::Document doc;
        doc.Load("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Load document from stream
        std::istringstream stream(inputData);
        rapidcsv::Document docStream(stream, labelParams, separatorParams, converterParams, lineReaderParams);

        // Test ToVal and ToStr
        rapidcsv::Converter<int> converter(converterParams);
        int value;
        std::string strValue;

        // Test ToVal
        converter.ToVal("123", value);

        // Test ToStr
        converter.ToStr(value, strValue);

        // Test SetCell
        doc.SetCell("Column1", "Row1", value);

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}