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

extern "C" int LLVMFuzzerTestOneInput_117(const uint8_t *Data, size_t Size) {
    // Prepare CSV data
    std::ofstream ofs("./dummy_file");
    if (!ofs.is_open()) return 0;
    ofs.write(reinterpret_cast<const char*>(Data), Size);
    ofs.close();

    // Initialize parameters
    rapidcsv::LabelParams labelParams;
    rapidcsv::SeparatorParams separatorParams{' ', true};
    rapidcsv::ConverterParams converterParams{true, 0.0, 0};
    rapidcsv::LineReaderParams lineReaderParams{true, '#'};

    try {
        // Create Document object
        std::ifstream ifs("./dummy_file");
        rapidcsv::Document doc(ifs, labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing GetRowCount
        size_t rowCount = doc.GetRowCount();
        
        // Fuzzing GetRow
        if (rowCount > 0) {
            auto row = doc.GetRow<std::string>(0);
        }

        // Fuzzing RemoveRow
        if (rowCount > 0) {
            doc.RemoveRow(0);
        }

        // Fuzzing SetRow
        if (rowCount > 0) {
            std::vector<std::string> newRow = {"new_data1", "new_data2"};
            doc.SetRow(0, newRow);
        }

        // Fuzzing InsertRow
        std::vector<std::string> insertRow = {"inserted_data1", "inserted_data2"};
        doc.InsertRow(rowCount, insertRow);

        // Fuzzing SetRowName
        if (rowCount > 0) {
            doc.SetRowName(0, "NewRowName");
        }

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}