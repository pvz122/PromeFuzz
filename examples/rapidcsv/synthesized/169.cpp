// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::RemoveRow at rapidcsv.h:1023:10 in rapidcsv.h
// rapidcsv::Document::InsertRow at rapidcsv.h:1052:10 in rapidcsv.h
// rapidcsv::Document::GetRowCount at rapidcsv.h:1095:12 in rapidcsv.h
// rapidcsv::Document::SetRowName at rapidcsv.h:1439:10 in rapidcsv.h
// rapidcsv::Document::GetRow at rapidcsv.h:891:20 in rapidcsv.h
// rapidcsv::Document::SetRow at rapidcsv.h:971:10 in rapidcsv.h
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

extern "C" int LLVMFuzzerTestOneInput_169(const uint8_t *Data, size_t Size) {
    // Prepare dummy CSV file
    std::ofstream outFile("./dummy_file");
    if (!outFile.is_open()) return 0;

    // Write random data to the CSV file
    for (size_t i = 0; i < Size; ++i) {
        outFile << static_cast<char>(Data[i]);
        if (i % 10 == 9) outFile << "\n"; // New line every 10 characters
    }
    outFile.close();

    try {
        // Set up parameters
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;

        // Create Document
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing various API functions
        size_t rowCount = doc.GetRowCount();
        if (rowCount > 0) {
            // Fuzz GetRow
            for (size_t i = 0; i < rowCount; ++i) {
                doc.GetRow<std::string>(i);
            }

            // Fuzz RemoveRow
            for (size_t i = 0; i < rowCount; ++i) {
                doc.RemoveRow(0); // Always remove the first row to avoid out-of-bounds
            }

            // Fuzz SetRow
            for (size_t i = 0; i < rowCount; ++i) {
                std::vector<std::string> rowData = {"data1", "data2", "data3"};
                doc.SetRow(i, rowData);
            }

            // Fuzz SetRowName
            for (size_t i = 0; i < rowCount; ++i) {
                doc.SetRowName(i, "RowName" + std::to_string(i));
            }

            // Fuzz InsertRow
            for (size_t i = 0; i < rowCount; ++i) {
                std::vector<std::string> newRow = {"newData1", "newData2"};
                doc.InsertRow(0, newRow, "NewRowName"); // Always insert at the beginning
            }
        }
    } catch (...) {
        // Catch any exceptions thrown by rapidcsv
    }

    return 0;
}