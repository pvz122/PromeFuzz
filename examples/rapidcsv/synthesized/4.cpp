// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::RemoveRow at rapidcsv.h:1034:10 in rapidcsv.h
// rapidcsv::Document::InsertRow at rapidcsv.h:1052:10 in rapidcsv.h
// rapidcsv::Document::GetRowCount at rapidcsv.h:1095:12 in rapidcsv.h
// rapidcsv::Document::GetRowName at rapidcsv.h:1423:17 in rapidcsv.h
// rapidcsv::Document::SetRowName at rapidcsv.h:1439:10 in rapidcsv.h
// rapidcsv::Document::GetRowIdx at rapidcsv.h:873:9 in rapidcsv.h
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
#include <vector>
#include <string>
#include <cstdint>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string inputData(reinterpret_cast<const char*>(Data), Size);
    
    // Write to dummy file
    std::ofstream outFile("./dummy_file");
    outFile << inputData;
    outFile.close();

    // Initialize parameters
    rapidcsv::LabelParams labelParams;
    rapidcsv::SeparatorParams separatorParams;
    rapidcsv::ConverterParams converterParams;
    rapidcsv::LineReaderParams lineReaderParams;

    // Create document
    try {
        std::ifstream inFile("./dummy_file");
        rapidcsv::Document doc(inFile, labelParams, separatorParams, converterParams, lineReaderParams);

        // Explore different API functions
        size_t rowCount = doc.GetRowCount();
        if (rowCount > 0) {
            // Test GetRowName
            for (size_t i = 0; i < rowCount; ++i) {
                try {
                    std::string rowName = doc.GetRowName(i);
                } catch (...) {}
            }

            // Test SetRowName
            for (size_t i = 0; i < rowCount; ++i) {
                try {
                    doc.SetRowName(i, "TestRowName");
                } catch (...) {}
            }

            // Test InsertRow
            for (size_t i = 0; i <= rowCount; ++i) {
                try {
                    doc.InsertRow(i, std::vector<std::string>{"TestData"}, "TestRow");
                } catch (...) {}
            }

            // Test RemoveRow
            try {
                doc.RemoveRow("TestRow");
            } catch (...) {}

            // Test GetRowIdx
            try {
                int rowIndex = doc.GetRowIdx("TestRow");
            } catch (...) {}
        }
    } catch (...) {
        // Handle exceptions for document creation
    }

    return 0;
}