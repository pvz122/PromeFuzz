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

extern "C" int LLVMFuzzerTestOneInput_114(const uint8_t *Data, size_t Size) {
    // Prepare a dummy file
    std::ofstream outFile("./dummy_file");
    if (!outFile.is_open()) {
        return 0;
    }
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        // Initialize parameters
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;

        // Create Document
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);

        // Explore different states
        size_t rowCount = doc.GetRowCount();
        for (size_t i = 0; i < rowCount + 1; ++i) {
            // Test GetRow
            if (i < rowCount) {
                auto rowData = doc.GetRow<std::string>(i);
            }

            // Test RemoveRow
            if (i < rowCount) {
                doc.RemoveRow(i);
            }

            // Test InsertRow
            doc.InsertRow(i, std::vector<std::string>{"Test", "Data"});

            // Test SetRow
            doc.SetRow<std::string>(i, std::vector<std::string>{"Updated", "Data"});
        }

        // Test SetRowName
        if (rowCount > 0) {
            doc.SetRowName(rowCount - 1, "LastRow");
        }

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}