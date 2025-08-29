// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Converter::ToStr at rapidcsv.h:133:10 in rapidcsv.h
// rapidcsv::Converter::ToVal at rapidcsv.h:171:10 in rapidcsv.h
// rapidcsv::Document::Load at rapidcsv.h:526:10 in rapidcsv.h
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
#include <cstdlib>
#include <fstream>
#include <string>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_140(const uint8_t *Data, size_t Size) {
    // Prepare the input data
    std::string csvData(reinterpret_cast<const char*>(Data), Size);
    const std::string path = "./dummy_file";

    // Write data to a dummy file
    std::ofstream outFile(path);
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
        // Test Load function with file path
        rapidcsv::Document doc(path, labelParams, separatorParams, converterParams, lineReaderParams);
        doc.Load(path, labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Test Load function with stream
        std::ifstream inFile(path);
        if (inFile.is_open()) {
            doc.Load(inFile, labelParams, separatorParams, converterParams, lineReaderParams);
            inFile.close();
        }

        // Test Save function
        doc.Save("./output_file.csv");

        // Test Converter functions
        rapidcsv::Converter<int> converter(converterParams);
        std::string strValue;
        converter.ToStr(42, strValue);
        int intValue;
        converter.ToVal("42", intValue);
    } catch (...) {
        // Catch exceptions
    }

    // Cleanup
    std::remove(path.c_str());
    std::remove("./output_file.csv");

    return 0;
}