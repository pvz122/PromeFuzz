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
#include <string>
#include <fstream>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size) {
    std::string inputData(reinterpret_cast<const char*>(Data), Size);
    
    // Prepare dummy CSV file
    const std::string dummyFilePath = "./dummy_file";
    std::ofstream dummyFile(dummyFilePath);
    if (dummyFile.is_open()) {
        dummyFile << inputData;
        dummyFile.close();
    }

    // Prepare parameters for rapidcsv functions
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
        // Test Document Load from file
        rapidcsv::Document doc(dummyFilePath, labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Test Document Load from stream
        std::istringstream stream(inputData);
        rapidcsv::Document docStream(stream, labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Test Converter ToVal and ToStr
        rapidcsv::Converter<int> converter(converterParams);
        int value;
        std::string strValue;
        
        converter.ToVal(inputData, value);
        converter.ToStr(value, strValue);
        
        // Test SetCell
        doc.SetCell("ColumnName", "RowName", value);
        
    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}