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
#include <iostream>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    // Prepare a temporary CSV file
    std::ofstream outfile("./dummy_file");
    if (!outfile.is_open()) {
        return 0;
    }

    // Write random data to the CSV file
    for (size_t i = 0; i < Size; ++i) {
        outfile << static_cast<char>(Data[i]);
        if (i % 10 == 9) {
            outfile << "\n";  // New line every 10 characters
        }
    }
    outfile.close();

    try {
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;

        // Create a Document object
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing GetRow with different row names
        for (size_t i = 0; i < 10; ++i) {
            std::string rowName = "Row" + std::to_string(i);
            doc.GetRow<std::string>(rowName); // Overload without conversion function
            // Use a conversion function compatible with ConvFunc
            doc.GetRow<std::string>(rowName, [](const std::string& val, std::string& out) { out = val; }); // Overload with conversion function
        }

        // Fuzzing SetRowName
        for (size_t i = 0; i < 10; ++i) {
            std::string newRowName = "NewRow" + std::to_string(i);
            doc.SetRowName(i, newRowName);
        }

        // Fuzzing RemoveRow
        for (size_t i = 0; i < 10; ++i) {
            std::string rowName = "Row" + std::to_string(i);
            doc.RemoveRow(rowName);
        }

        // Fuzzing InsertRow
        for (size_t i = 0; i < 10; ++i) {
            std::vector<std::string> newRow = {"Data1", "Data2", "Data3"};
            std::string rowName = "InsertedRow" + std::to_string(i);
            doc.InsertRow(i, newRow, rowName);
        }

        // Fuzzing GetRowIdx
        for (size_t i = 0; i < 10; ++i) {
            std::string rowName = "Row" + std::to_string(i);
            doc.GetRowIdx(rowName);
        }

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}