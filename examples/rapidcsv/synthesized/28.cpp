// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::InsertRow at rapidcsv.h:1052:10 in rapidcsv.h
// rapidcsv::Document::SetCell at rapidcsv.h:1345:10 in rapidcsv.h
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

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    // Prepare dummy file path
    const std::string dummyFilePath = "./dummy_file";
    
    // Write random data to the dummy file
    std::ofstream dummyFile(dummyFilePath, std::ios::binary);
    if (dummyFile.is_open()) {
        dummyFile.write(reinterpret_cast<const char*>(Data), Size);
        dummyFile.close();
    }

    try {
        // Create a Document object
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;

        rapidcsv::Document doc(dummyFilePath, labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing Save function
        doc.Save(dummyFilePath);

        // Fuzzing Clear function
        doc.Clear();

        // Fuzzing InsertColumn function
        std::vector<std::string> columnData = {"data1", "data2", "data3"};
        doc.InsertColumn(0, columnData, "NewColumn");

        // Fuzzing InsertRow function
        std::vector<std::string> rowData = {"row1", "row2", "row3"};
        doc.InsertRow(0, rowData, "NewRow");

        // Fuzzing SetCell function
        doc.SetCell("NewColumn", 0, "UpdatedData");

        // Fuzzing SetColumnName function
        doc.SetColumnName(0, "UpdatedColumnName");

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}