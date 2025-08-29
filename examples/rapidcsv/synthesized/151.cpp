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

extern "C" int LLVMFuzzerTestOneInput_151(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file
    const std::string dummyFilePath = "./dummy_file.csv";
    std::ofstream dummyFile(dummyFilePath, std::ios::binary);
    if (!dummyFile.is_open()) {
        return 0;
    }
    
    // Write random data to the dummy file
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    try {
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;

        // Create a Document object
        rapidcsv::Document doc(dummyFilePath, labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing GetRow
        size_t rowCount = doc.GetRowCount();
        if (rowCount > 0) {
            doc.GetRow<std::string>(0, [](const std::string& val, std::string& out) { out = val; }); // Valid conversion function
        }

        // Fuzzing RemoveRow
        if (rowCount > 0) {
            doc.RemoveRow(0);
        }

        // Fuzzing SetRow
        if (rowCount > 0) {
            std::vector<std::string> rowData = {"Test", "Data"};
            doc.SetRow(0, rowData);
        }

        // Fuzzing SetRowName
        if (rowCount > 0) {
            doc.SetRowName(0, "NewRowName");
        }

        // Fuzzing InsertRow
        std::vector<std::string> newRowData = {"Inserted", "Row"};
        doc.InsertRow(0, newRowData, "InsertedRow");

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}