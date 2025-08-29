// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::RemoveRow at rapidcsv.h:1023:10 in rapidcsv.h
// rapidcsv::Document::InsertRow at rapidcsv.h:1052:10 in rapidcsv.h
// rapidcsv::Document::GetRowCount at rapidcsv.h:1095:12 in rapidcsv.h
// rapidcsv::Document::SetRowName at rapidcsv.h:1439:10 in rapidcsv.h
// rapidcsv::Document::GetRow at rapidcsv.h:915:20 in rapidcsv.h
// rapidcsv::Document::SetRow at rapidcsv.h:971:10 in rapidcsv.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstdint>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_154(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file
    std::ofstream dummyFile("./dummy_file.csv");
    if (!dummyFile.is_open()) return 0;

    // Write random data to the dummy CSV file
    for (size_t i = 0; i < Size; ++i) {
        dummyFile << static_cast<char>(Data[i]);
        if (i % 10 == 9) dummyFile << '\n'; // New line every 10 characters
    }
    dummyFile.close();

    // Initialize parameters for Document
    rapidcsv::LabelParams labelParams;
    rapidcsv::SeparatorParams separatorParams;
    rapidcsv::ConverterParams converterParams;
    rapidcsv::LineReaderParams lineReaderParams;

    try {
        std::ifstream stream("./dummy_file.csv");
        rapidcsv::Document doc(stream, labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing GetRow
        size_t rowCount = doc.GetRowCount();
        if (rowCount > 0) {
            for (size_t idx = 0; idx < rowCount; ++idx) {
                doc.GetRow<std::string>(idx, [](const std::string& val, std::string& out) { out = val; });
            }
        }

        // Fuzzing RemoveRow
        if (rowCount > 0) {
            doc.RemoveRow(0); // Remove first row
        }

        // Fuzzing SetRow
        if (rowCount > 0) {
            std::vector<std::string> newRow = {"New", "Data", "Row"};
            doc.SetRow(0, newRow);
        }

        // Fuzzing SetRowName
        if (rowCount > 0) {
            doc.SetRowName(0, "NewRowName");
        }

        // Fuzzing InsertRow
        std::vector<std::string> insertRow = {"Inserted", "Row"};
        doc.InsertRow(1, insertRow, "InsertedRowName");

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}