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
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_175(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string csvData(reinterpret_cast<const char*>(Data), Size);
    std::ofstream outFile("./dummy_file");
    outFile << csvData;
    outFile.close();

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

    try {
        // Test Load from file
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Test Load from stream
        std::istringstream stream(csvData);
        doc.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);

        // Test SetCell
        doc.SetCell<std::string>("Column1", "Row1", "Test Data");

        // Test Converter ToVal and ToStr
        rapidcsv::Converter<int> converter(converterParams);
        int value;
        converter.ToVal("123", value);
        std::string strValue;
        converter.ToStr(value, strValue);
    } catch (...) {
        // Catch any exceptions thrown by rapidcsv
    }

    return 0;
}