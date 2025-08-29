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
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_164(const uint8_t *Data, size_t Size) {
    // Prepare the dummy CSV file
    std::ofstream outfile("./dummy_file");
    if (!outfile.is_open()) return 0;

    // Write random data to the file based on the input size
    for (size_t i = 0; i < Size; ++i) {
        outfile << static_cast<char>(Data[i] % 128); // Limit to printable ASCII
        if ((i + 1) % 10 == 0) outfile << '\n'; // New line every 10 characters
    }
    outfile.close();

    try {
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;

        // Create Document instance
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing GetRow
        size_t rowCount = doc.GetRowCount();
        if (rowCount > 0) {
            for (size_t i = 0; i < rowCount; ++i) {
                doc.GetRow<std::string>(i, [](const std::string& val, std::string& out) { out = val; });
            }
        }

        // Fuzzing RemoveRow
        if (rowCount > 0) {
            doc.RemoveRow(0); // Try removing the first row
        }

        // Fuzzing SetRow
        if (rowCount > 0) {
            std::vector<std::string> newRow = {"new", "data", "row"};
            doc.SetRow(0, newRow);
        }

        // Fuzzing SetRowName
        if (rowCount > 0) {
            doc.SetRowName(0, "NewRowName");
        }

        // Fuzzing InsertRow
        std::vector<std::string> insertRow = {"inserted", "row"};
        doc.InsertRow(rowCount, insertRow, "InsertedRowName");
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}