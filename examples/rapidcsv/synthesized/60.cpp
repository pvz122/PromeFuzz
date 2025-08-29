// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetColumnName at rapidcsv.h:1377:10 in rapidcsv.h
// rapidcsv::Document::GetColumnIdx at rapidcsv.h:608:9 in rapidcsv.h
// rapidcsv::Document::GetColumn at rapidcsv.h:702:20 in rapidcsv.h
// rapidcsv::Document::SetColumn at rapidcsv.h:756:10 in rapidcsv.h
// rapidcsv::Document::RemoveColumn at rapidcsv.h:788:10 in rapidcsv.h
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
#include <fstream>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size) {
    // Prepare dummy CSV file
    std::ofstream ofs("./dummy_file");
    if (!ofs.is_open()) return 0;

    // Write random data to the dummy CSV file
    ofs << "Column1,Column2,Column3\n";
    for (size_t i = 0; i < Size % 10 + 1; ++i) {
        ofs << std::string(reinterpret_cast<const char*>(Data), Size < 10 ? Size : 10) << "\n";
    }
    ofs.close();

    try {
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;

        // Create Document from the dummy file
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing RemoveColumn
        if (Size > 0) {
            std::string columnName(reinterpret_cast<const char*>(Data), Size < 10 ? Size : 10);
            doc.RemoveColumn(columnName);
        }

        // Fuzzing SetColumn
        if (Size > 1) {
            std::string columnName(reinterpret_cast<const char*>(Data), Size < 10 ? Size : 10);
            std::vector<std::string> columnData = {std::string(reinterpret_cast<const char*>(Data), Size < 10 ? Size : 10)};
            doc.SetColumn(columnName, columnData);
        }

        // Fuzzing GetColumnIdx
        if (Size > 2) {
            std::string columnName(reinterpret_cast<const char*>(Data), Size < 10 ? Size : 10);
            doc.GetColumnIdx(columnName);
        }

        // Fuzzing InsertColumn
        if (Size > 3) {
            std::vector<std::string> columnData = {std::string(reinterpret_cast<const char*>(Data), Size < 10 ? Size : 10)};
            std::string columnName(reinterpret_cast<const char*>(Data), Size < 10 ? Size : 10);
            doc.InsertColumn(Size % 3, columnData, columnName);
        }

        // Fuzzing GetColumn
        if (Size > 4) {
            std::string columnName(reinterpret_cast<const char*>(Data), Size < 10 ? Size : 10);
            doc.GetColumn<std::string>(columnName, [](const std::string& val, std::string& out) { out = val; });
        }

        // Fuzzing SetColumnName
        if (Size > 5) {
            std::string columnName(reinterpret_cast<const char*>(Data), Size < 10 ? Size : 10);
            doc.SetColumnName(Size % 3, columnName);
        }
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}