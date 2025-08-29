// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::RemoveRow at rapidcsv.h:1034:10 in rapidcsv.h
// rapidcsv::Document::InsertRow at rapidcsv.h:1052:10 in rapidcsv.h
// rapidcsv::Document::SetRowName at rapidcsv.h:1439:10 in rapidcsv.h
// rapidcsv::Document::GetRowIdx at rapidcsv.h:873:9 in rapidcsv.h
// rapidcsv::Document::GetRow at rapidcsv.h:938:20 in rapidcsv.h
// rapidcsv::Document::GetRow at rapidcsv.h:955:20 in rapidcsv.h
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
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    // Prepare dummy file
    std::ofstream dummyFile("./dummy_file");
    if (!dummyFile.is_open()) return 0;

    // Fill dummy file with random CSV data
    std::string csvData;
    for (size_t i = 0; i < Size; ++i) {
        csvData += static_cast<char>(Data[i] % 128); // Limit to valid ASCII range
        if ((i + 1) % 10 == 0) csvData += '\n'; // Newline every 10 characters
    }
    dummyFile << csvData;
    dummyFile.close();

    try {
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;

        // Create document
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing GetRow with different row names
        std::string rowName = "Row" + std::to_string(rand() % 100);
        doc.GetRow<std::string>(rowName);
        doc.GetRow<int>(rowName, [](const std::string& val, int& out) {
            out = std::stoi(val);
        });

        // Fuzzing SetRowName
        size_t rowIndex = rand() % 100;
        doc.SetRowName(rowIndex, rowName);

        // Fuzzing RemoveRow
        doc.RemoveRow(rowName);

        // Fuzzing InsertRow
        std::vector<std::string> newRow = {"Data1", "Data2", "Data3"};
        doc.InsertRow(rowIndex, newRow, rowName);

        // Fuzzing GetRowIdx
        doc.GetRowIdx(rowName);
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}