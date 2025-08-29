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
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_162(const uint8_t *Data, size_t Size) {
    // Prepare the CSV data
    std::string csvData(reinterpret_cast<const char*>(Data), Size);
    std::ofstream outFile("./dummy_file");
    outFile << csvData;
    outFile.close();

    // Initialize parameters
    rapidcsv::LabelParams labelParams;
    rapidcsv::SeparatorParams separatorParams{ ',', true };
    rapidcsv::ConverterParams converterParams{ true, 0.0, 0 };
    rapidcsv::LineReaderParams lineReaderParams{ true, '#' };

    try {
        // Create Document
        std::ifstream inFile("./dummy_file");
        rapidcsv::Document doc(inFile, labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing GetRowCount
        size_t rowCount = doc.GetRowCount();

        // Fuzzing InsertRow
        std::vector<std::string> newRow = { "new", "data", "row" };
        doc.InsertRow(rowCount, newRow, "NewRow");

        // Fuzzing SetRow
        if (rowCount > 0) {
            doc.SetRow(0, newRow);
        }

        // Fuzzing GetRow
        if (rowCount > 0) {
            auto rowData = doc.GetRow<std::string>(0, [](const std::string& val, std::string& out) { out = val; });
        }

        // Fuzzing RemoveRow
        if (rowCount > 0) {
            doc.RemoveRow(0);
        }

        // Fuzzing SetRowName
        if (rowCount > 0) {
            doc.SetRowName(0, "UpdatedRow");
        }

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}