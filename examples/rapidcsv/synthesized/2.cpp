// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetColumnName at rapidcsv.h:1377:10 in rapidcsv.h
// rapidcsv::Document::GetColumnIdx at rapidcsv.h:608:9 in rapidcsv.h
// rapidcsv::Document::GetColumn at rapidcsv.h:702:20 in rapidcsv.h
// rapidcsv::Document::SetColumn at rapidcsv.h:756:10 in rapidcsv.h
// rapidcsv::Document::RemoveColumn at rapidcsv.h:788:10 in rapidcsv.h
// rapidcsv::Document::InsertColumn at rapidcsv.h:806:10 in rapidcsv.h
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

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file
    std::ofstream ofs("./dummy_file");
    if (!ofs.is_open()) return 0;

    // Write random data to the CSV file based on the input Data
    for (size_t i = 0; i < Size; ++i) {
        ofs << std::string(1, static_cast<char>(Data[i]));
        if (i % 10 == 9) ofs << '\n'; // New line every 10 characters
    }
    ofs.close();

    try {
        // Create a Document object
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;

        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing RemoveColumn
        doc.RemoveColumn("ColumnName"); // Test with a random column name

        // Fuzzing SetColumn
        std::vector<int> columnData = {1, 2, 3, 4, 5};
        doc.SetColumn("ColumnName", columnData);

        // Fuzzing GetColumnIdx
        int index = doc.GetColumnIdx("ColumnName");

        // Fuzzing InsertColumn
        std::vector<int> newColumnData = {6, 7, 8, 9, 10};
        doc.InsertColumn(index, newColumnData, "NewColumnName");

        // Fuzzing GetColumn
        auto retrievedColumn = doc.GetColumn<int>("NewColumnName", [](const std::string& val, int& out) {
            out = std::stoi(val);
        });

        // Fuzzing SetColumnName
        doc.SetColumnName(index, "UpdatedColumnName");

    } catch (...) {
        // Catch any exceptions thrown by rapidcsv
    }

    return 0;
}