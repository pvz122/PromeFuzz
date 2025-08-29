// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetCell at rapidcsv.h:1327:10 in rapidcsv.h
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
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <rapidcsv.h>

extern "C" int LLVMFuzzerTestOneInput_183(const uint8_t *Data, size_t Size) {
    // Prepare dummy CSV file
    std::ofstream outFile("./dummy_file");
    if (!outFile.is_open()) return 0;

    // Write random data to the CSV file
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        rapidcsv::Document doc;

        // Load CSV from file
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

        // Fuzzing Load function
        doc.Load("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Fuzzing Load from stream
        std::ifstream inFile("./dummy_file");
        if (inFile.is_open()) {
            doc.Load(inFile, labelParams, separatorParams, converterParams, lineReaderParams);
            inFile.close();
        }

        // Fuzzing SetCell function
        std::string rowName = "testRow";
        int columnIdx = 0;
        doc.SetCell(columnIdx, rowName, "testValue");

        // Fuzzing Converter ToVal and ToStr
        rapidcsv::Converter<int> converter(converterParams);
        int val;
        converter.ToVal("123", val);
        std::string str;
        converter.ToStr(val, str);
        
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}