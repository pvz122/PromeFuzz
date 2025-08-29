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
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_120(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file
    std::ofstream dummyFile("./dummy_file");
    if (!dummyFile.is_open()) return 0;

    // Write random data to the file
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    // Initialize parameters for the Document
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
        // Test the Load function with the file path
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Test the Load function with an input stream
        std::ifstream inputStream("./dummy_file");
        if (inputStream.is_open()) {
            doc.Load(inputStream, labelParams, separatorParams, converterParams, lineReaderParams);
            inputStream.close();
        }

        // Test the Save function
        doc.Save("./output_file");

        // Test the Converter functions (ToStr and ToVal)
        rapidcsv::Converter<int> converter(converterParams);
        std::string strValue;
        int intValue;

        // Test ToStr
        converter.ToStr(42, strValue);

        // Test ToVal
        converter.ToVal("42", intValue);

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}