// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetColumnName at rapidcsv.h:1377:10 in rapidcsv.h
// rapidcsv::Document::GetColumnIdx at rapidcsv.h:608:9 in rapidcsv.h
// rapidcsv::Document::SetColumn at rapidcsv.h:718:10 in rapidcsv.h
// rapidcsv::Document::RemoveColumn at rapidcsv.h:770:10 in rapidcsv.h
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
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file
    std::ofstream dummyFile("./dummy_file");
    if (!dummyFile.is_open()) return 0;

    // Write random data to the CSV file
    for (size_t i = 0; i < Size; ++i) {
        dummyFile << std::string(1, static_cast<char>(Data[i]));
        if (i % 10 == 9) dummyFile << "\n"; // New line every 10 characters
    }
    dummyFile.close();

    try {
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;

        // Create a Document object
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing RemoveColumn
        size_t colIdxToRemove = Size % 10; // Random index to remove
        doc.RemoveColumn(colIdxToRemove);

        // Fuzzing SetColumn
        std::vector<std::string> columnData = {"data1", "data2", "data3"};
        size_t colIdxToSet = Size % 10; // Random index to set
        doc.SetColumn(colIdxToSet, columnData);

        // Fuzzing GetColumnIdx
        std::string columnName = "ColumnName";
        int columnIdx = doc.GetColumnIdx(columnName);

        // Fuzzing InsertColumn
        std::vector<std::string> newColumnData = {"new1", "new2", "new3"};
        size_t colIdxToInsert = Size % 10; // Random index to insert
        doc.InsertColumn(colIdxToInsert, newColumnData, "NewColumn");

        // Fuzzing SetColumnName
        std::string newColName = "UpdatedColumnName";
        doc.SetColumnName(colIdxToInsert, newColName);

    } catch (...) {
        // Catch any exceptions thrown by rapidcsv
    }

    return 0;
}