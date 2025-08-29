// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetCell at rapidcsv.h:1303:10 in rapidcsv.h
// rapidcsv::Converter::ToStr at rapidcsv.h:133:10 in rapidcsv.h
// rapidcsv::Converter::ToVal at rapidcsv.h:171:10 in rapidcsv.h
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
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_176(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string input(reinterpret_cast<const char*>(Data), Size);
    
    // Write data to a dummy file
    std::ofstream dummyFile("./dummy_file");
    if (dummyFile.is_open()) {
        dummyFile << input;
        dummyFile.close();
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

    try {
        // Fuzzing Load from file
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Fuzzing Load from stream
        std::istringstream stream(input);
        doc.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Fuzzing SetCell
        doc.SetCell<std::string>("Column1", "Row1", "TestValue");
        
        // Fuzzing Converter ToVal and ToStr with int type
        rapidcsv::Converter<int> converter(converterParams);
        std::string strValue = "123";
        int intValue;
        converter.ToVal(strValue, intValue);
        std::string outStr;
        converter.ToStr(intValue, outStr);
        
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}