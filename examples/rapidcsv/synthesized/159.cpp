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
#include <iostream>
#include <fstream>
#include <string>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_159(const uint8_t *Data, size_t Size) {
    // Prepare the data for the CSV file
    std::string csvData(reinterpret_cast<const char*>(Data), Size);
    const std::string filePath = "./dummy_file";

    // Write the data to a temporary CSV file
    std::ofstream outFile(filePath);
    outFile << csvData;
    outFile.close();

    try {
        rapidcsv::LabelParams labelParams{0};
        rapidcsv::SeparatorParams separatorParams{',', true};
        rapidcsv::ConverterParams converterParams{true, 0.0, 0};
        rapidcsv::LineReaderParams lineReaderParams{true, '#'};

        // Test the Load function with file path
        rapidcsv::Document doc(filePath);
        doc.Load(filePath, labelParams, separatorParams, converterParams, lineReaderParams);

        // Test the Load function with a stream
        std::ifstream inFile(filePath);
        if (inFile.is_open()) {
            doc.Load(inFile, labelParams, separatorParams, converterParams, lineReaderParams);
            inFile.close();
        }

        // Test GetColumnName with various indices
        for (size_t i = 0; i < 10; ++i) { // Arbitrary limit to avoid out-of-bounds
            try {
                std::string columnName = doc.GetColumnName(i);
            } catch (...) {
                // Catch any exceptions thrown by GetColumnName
            }
        }

        // Test Converter::ToVal and Converter::ToStr with dummy values
        rapidcsv::Converter<int> intConverter(converterParams);
        int dummyVal;
        std::string dummyStr = "123";
        intConverter.ToVal(dummyStr, dummyVal);
        intConverter.ToStr(dummyVal, dummyStr);

    } catch (...) {
        // Catch any exceptions thrown by the Document or Converter methods
    }

    // Cleanup: remove the dummy CSV file
    std::remove(filePath.c_str());

    return 0;
}