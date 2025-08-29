// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Converter::ToStr at rapidcsv.h:133:10 in rapidcsv.h
// rapidcsv::Document::GetColumnName at rapidcsv.h:1361:17 in rapidcsv.h
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
#include <string>
#include <vector>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_152(const uint8_t *Data, size_t Size) {
    // Prepare dummy CSV file
    std::string dummyFilePath = "./dummy_file.csv";
    std::ofstream dummyFile(dummyFilePath, std::ios::binary);
    if (!dummyFile.is_open()) return 0;

    // Write the fuzz data to the dummy file
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    try {
        // Create default parameters
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;

        // Test Document Load from file
        rapidcsv::Document doc(dummyFilePath);
        doc.Load(dummyFilePath, labelParams, separatorParams, converterParams, lineReaderParams);

        // Test Document Load from stream
        std::ifstream stream(dummyFilePath);
        if (stream.is_open()) {
            doc.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);
            stream.close();
        }

        // Test GetColumnName with various indices
        for (size_t i = 0; i < 10; ++i) { // Arbitrary limit for fuzzing
            doc.GetColumnName(i);
        }

        // Test Converter ToVal and ToStr
        rapidcsv::Converter<int> intConverter(converterParams);
        std::string strValue = "123";
        int intValue;
        intConverter.ToVal(strValue, intValue);
        std::string outputStr;
        intConverter.ToStr(intValue, outputStr);

    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}