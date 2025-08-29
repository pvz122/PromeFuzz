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

extern "C" int LLVMFuzzerTestOneInput_163(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string inputData(reinterpret_cast<const char*>(Data), Size);
    const std::string filePath = "./dummy_file";

    // Write the input data to a dummy file
    std::ofstream outFile(filePath);
    outFile << inputData;
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
        rapidcsv::Document doc(filePath, labelParams, separatorParams, converterParams, lineReaderParams);
        doc.Load(filePath, labelParams, separatorParams, converterParams, lineReaderParams);

        // Test Load from stream
        std::istringstream stream(inputData);
        doc.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);

        // Test SetCell
        doc.SetCell<std::string>("Column1", 0, "TestValue");

        // Test Converter::ToVal and ToStr with a specific type
        rapidcsv::Converter<long double> converter(converterParams);
        std::string testStr = "123.45";
        long double val;
        converter.ToVal(testStr, val);
        std::string outStr;
        converter.ToStr(val, outStr);
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}