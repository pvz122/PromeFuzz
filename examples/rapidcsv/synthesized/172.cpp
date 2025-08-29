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
#include <fstream>
#include <iostream>
#include <string>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_172(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string input(reinterpret_cast<const char*>(Data), Size);
    
    // Create a dummy CSV file
    std::ofstream ofs("./dummy_file");
    ofs << input;
    ofs.close();

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
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Test Load from stream
        std::istringstream stream(input);
        rapidcsv::Document docStream(stream, labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Test SetCell
        doc.SetCell<std::string>("Column1", "Row1", "TestValue");
        
        // Test Converter ToVal
        rapidcsv::Converter<int> converter(converterParams); // Specify the type for Converter
        std::string strValue = "123";
        int intValue;
        converter.ToVal(strValue, intValue);
        
        // Test Converter ToStr
        std::string outputStr;
        converter.ToStr(intValue, outputStr);
        
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}