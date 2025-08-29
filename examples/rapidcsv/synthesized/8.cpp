// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::GetRowCount at rapidcsv.h:1095:12 in rapidcsv.h
// rapidcsv::Document::GetCell at rapidcsv.h:1230:7 in rapidcsv.h
// rapidcsv::Document::SetCell at rapidcsv.h:1345:10 in rapidcsv.h
// rapidcsv::Document::GetColumnNames at rapidcsv.h:1406:30 in rapidcsv.h
// rapidcsv::Document::GetRowName at rapidcsv.h:1423:17 in rapidcsv.h
// rapidcsv::Document::GetColumn at rapidcsv.h:626:20 in rapidcsv.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <fstream>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file
    std::ofstream outFile("./dummy_file");
    if (!outFile.is_open()) return 0;

    // Write random data to the CSV file
    for (size_t i = 0; i < Size; ++i) {
        outFile << static_cast<char>(Data[i]);
        if (i % 10 == 9) outFile << '\n'; // New line every 10 characters
    }
    outFile.close();

    try {
        // Create a Document object
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;

        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);

        // Test GetRowCount
        size_t rowCount = doc.GetRowCount();

        // Test GetRowName with random indices
        std::vector<std::string> rowNames;
        for (size_t i = 0; i < rowCount; ++i) {
            rowNames.push_back(doc.GetRowName(i));
        }

        // Test GetColumnNames
        std::vector<std::string> columnNames = doc.GetColumnNames();

        // Test GetCell with random column index and row name
        for (size_t i = 0; i < columnNames.size() && i < rowCount; ++i) {
            std::string cellValue = doc.GetCell<std::string>(i, rowNames[i]);
        }

        // Test GetColumn with random column index
        for (size_t i = 0; i < columnNames.size(); ++i) {
            std::vector<std::string> columnData = doc.GetColumn<std::string>(i);
        }

        // Test SetCell with random data
        if (!columnNames.empty() && rowCount > 0) {
            doc.SetCell<std::string>(columnNames[0], 0, "TestValue");
        }

    } catch (...) {
        // Catch all exceptions to avoid crashing
    }

    return 0;
}