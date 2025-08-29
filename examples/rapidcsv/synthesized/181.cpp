// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetCell at rapidcsv.h:1327:10 in rapidcsv.h
// rapidcsv::Document::GetColumnName at rapidcsv.h:1361:17 in rapidcsv.h
// rapidcsv::Document::GetColumnNames at rapidcsv.h:1406:30 in rapidcsv.h
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
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_181(const uint8_t *Data, size_t Size) {
    // Prepare dummy CSV file
    const std::string filePath = "./dummy_file.csv";
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile) return 0;

    // Write random data to the CSV file
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;

        // Load CSV using both overloads
        rapidcsv::Document doc1(filePath);
        doc1.Load(filePath, labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Test GetColumnName with random indices
        size_t columnCount = doc1.GetColumnNames().size();
        if (columnCount > 0) {
            for (size_t i = 0; i < columnCount; ++i) {
                std::string columnName = doc1.GetColumnName(i);
            }
        }

        // Modify a cell with random values
        if (columnCount > 0) {
            std::string randomRowName = "Row" + std::to_string(rand() % 100);
            doc1.SetCell(0, randomRowName, "TestValue");
        }

    } catch (...) {
        // Catch any exceptions thrown by rapidcsv
    }

    return 0;
}