// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Converter::ToStr at rapidcsv.h:133:10 in rapidcsv.h
// rapidcsv::Document::GetColumnName at rapidcsv.h:1361:17 in rapidcsv.h
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
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_158(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file
    std::string dummyFilePath = "./dummy_file";
    std::ofstream dummyFile(dummyFilePath, std::ios::binary);
    if (!dummyFile.is_open()) return 0;

    // Write random data to the dummy file
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    try {
        // Initialize parameters
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;

        // Test the Load function with the file
        rapidcsv::Document doc(dummyFilePath);
        doc.Load(dummyFilePath, labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzz GetColumnName with various indices
        size_t columnCount = 10; // Arbitrary value for testing
        for (size_t i = 0; i < columnCount; ++i) {
            doc.GetColumnName(i);
        }

        // Fuzz Converter ToVal and ToStr
        rapidcsv::Converter<int> converter(converterParams);
        std::string testStr = "123";
        int testVal = 0;
        converter.ToVal(testStr, testVal);
        std::string outStr;
        converter.ToStr(testVal, outStr);

    } catch (...) {
        // Catch any exceptions thrown by rapidcsv
    }

    return 0;
}