// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::InsertRow at rapidcsv.h:1052:10 in rapidcsv.h
// rapidcsv::Document::SetCell at rapidcsv.h:1327:10 in rapidcsv.h
// rapidcsv::Document::SetColumnName at rapidcsv.h:1377:10 in rapidcsv.h
// rapidcsv::Document::Save at rapidcsv.h:569:10 in rapidcsv.h
// rapidcsv::Document::Clear at rapidcsv.h:591:10 in rapidcsv.h
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
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    // Prepare a dummy file for writing CSV data
    const std::string dummyFilePath = "./dummy_file";
    
    // Generate random data for testing
    std::string csvData(reinterpret_cast<const char*>(Data), Size);
    std::ofstream outFile(dummyFilePath);
    outFile << csvData;
    outFile.close();

    // Create LabelParams, SeparatorParams, ConverterParams, and LineReaderParams with default values
    rapidcsv::LabelParams labelParams;
    rapidcsv::SeparatorParams separatorParams;
    rapidcsv::ConverterParams converterParams;
    rapidcsv::LineReaderParams lineReaderParams;

    try {
        // Initialize Document with the dummy file
        rapidcsv::Document doc(dummyFilePath, labelParams, separatorParams, converterParams, lineReaderParams);

        // Test various API functions
        doc.Clear();

        // Insert a column with random data
        std::vector<std::string> columnData = {"test1", "test2", "test3"};
        doc.InsertColumn(0, columnData, "Column1");

        // Insert a row with random data
        std::vector<std::string> rowData = {"row1", "row2", "row3"};
        doc.InsertRow(0, rowData, "Row1");

        // Set a cell value
        doc.SetCell(0, "Row1", "UpdatedValue");

        // Set a column name
        doc.SetColumnName(0, "UpdatedColumn");

        // Save document to the dummy file
        doc.Save(dummyFilePath);
    } catch (...) {
        // Catch any exceptions thrown by rapidcsv
    }

    return 0;
}