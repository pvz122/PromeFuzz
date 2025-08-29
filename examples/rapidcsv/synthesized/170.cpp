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
#include <fstream>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_170(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file
    std::ofstream ofs("./dummy_file");
    if (!ofs.is_open()) return 0;
    
    // Write random data to the file based on the input data size
    for (size_t i = 0; i < Size; ++i) {
        ofs << std::string(1, static_cast<char>(Data[i] % 128)); // Keep it printable
        if (i % 10 == 9) ofs << "\n"; // New line every 10 characters
    }
    ofs.close();

    // Prepare parameters for Document constructor
    rapidcsv::LabelParams labelParams;
    rapidcsv::SeparatorParams separatorParams;
    rapidcsv::ConverterParams converterParams;
    rapidcsv::LineReaderParams lineReaderParams;

    try {
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing GetRow
        size_t rowCount = doc.GetRowCount();
        if (rowCount > 0) {
            for (size_t idx = 0; idx < rowCount; ++idx) {
                doc.GetRow<std::string>(idx, [](const std::string& val, std::string& out) {
                    out = val; 
                });
            }
        }

        // Fuzzing RemoveRow
        if (rowCount > 0) {
            for (size_t idx = 0; idx < rowCount; ++idx) {
                doc.RemoveRow(idx);
            }
        }

        // Fuzzing SetRow
        if (rowCount > 0) {
            for (size_t idx = 0; idx < rowCount; ++idx) {
                std::vector<std::string> rowData = {"data1", "data2", "data3"};
                doc.SetRow(idx, rowData);
            }
        }

        // Fuzzing SetRowName
        if (rowCount > 0) {
            for (size_t idx = 0; idx < rowCount; ++idx) {
                doc.SetRowName(idx, "RowName" + std::to_string(idx));
            }
        }

        // Fuzzing InsertRow
        if (rowCount > 0) {
            for (size_t idx = 0; idx <= rowCount; ++idx) {
                std::vector<std::string> newRow = {"newData1", "newData2"};
                doc.InsertRow(idx, newRow, "InsertedRow");
            }
        }

    } catch (...) {
        // Catch any exceptions thrown by rapidcsv
    }

    return 0;
}