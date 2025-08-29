// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Converter::ToStr at rapidcsv.h:133:10 in rapidcsv.h
// rapidcsv::Converter::ToVal at rapidcsv.h:171:10 in rapidcsv.h
// rapidcsv::Document::Load at rapidcsv.h:549:10 in rapidcsv.h
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
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_136(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file
    std::ofstream dummyFile("./dummy_file");
    if (!dummyFile.is_open()) {
        return 0;
    }

    // Write the fuzz data to the dummy file
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

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

    // Fuzzing the Load function with file path
    try {
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Catch exceptions from the Document constructor
    }

    // Fuzzing the Load function with input stream
    try {
        std::ifstream inputStream("./dummy_file");
        if (inputStream.is_open()) {
            rapidcsv::Document doc;
            doc.Load(inputStream, labelParams, separatorParams, converterParams, lineReaderParams);
        }
    } catch (...) {
        // Catch exceptions from Load function
    }

    // Fuzzing the Save function
    try {
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
        doc.Save("./output_file");
    } catch (...) {
        // Catch exceptions from Save function
    }

    // Fuzzing Converter ToStr and ToVal
    try {
        rapidcsv::Converter<int> converter(converterParams);
        std::string strValue;
        converter.ToStr(123, strValue);
        int intValue;
        converter.ToVal("123", intValue);
    } catch (...) {
        // Catch exceptions from Converter functions
    }

    return 0;
}