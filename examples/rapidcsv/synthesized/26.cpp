// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::GetCell at rapidcsv.h:1193:7 in rapidcsv.h
// rapidcsv::Document::GetCell at rapidcsv.h:1230:7 in rapidcsv.h
// rapidcsv::Document::SetCell at rapidcsv.h:1327:10 in rapidcsv.h
// rapidcsv::Document::SetCell at rapidcsv.h:1345:10 in rapidcsv.h
// rapidcsv::Document::GetColumnName at rapidcsv.h:1361:17 in rapidcsv.h
// rapidcsv::Document::GetColumnNames at rapidcsv.h:1406:30 in rapidcsv.h
// rapidcsv::Document::GetColumn at rapidcsv.h:702:20 in rapidcsv.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <rapidcsv.h>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    // Prepare dummy CSV file
    std::ofstream outFile("./dummy_file");
    if (!outFile.is_open()) return 0;

    // Write fuzzy data to the CSV file
    std::string csvData(reinterpret_cast<const char*>(Data), Size);
    outFile << csvData;
    outFile.close();

    try {
        // Initialize the Document
        std::ifstream inFile("./dummy_file");
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;
        rapidcsv::Document doc(inFile, labelParams, separatorParams, converterParams, lineReaderParams);

        // Explore GetColumn
        if (doc.GetColumnNames().size() > 0) {
            std::string columnName = doc.GetColumnName(0);
            doc.GetColumn<std::string>(columnName, [](const std::string& val, std::string& out) { out = val; });
        }

        // Explore GetCell overloads
        if (doc.GetColumnNames().size() > 0) {
            std::string columnName = doc.GetColumnName(0);
            doc.GetCell<std::string>(columnName, 0);
            doc.GetCell<std::string>(0, columnName);
        }

        // Explore SetCell overloads
        if (doc.GetColumnNames().size() > 0) {
            std::string columnName = doc.GetColumnName(0);
            doc.SetCell<std::string>(columnName, 0, "TestValue");
            doc.SetCell<std::string>(0, columnName, "TestValue");
        }

        // Explore GetColumnName
        if (doc.GetColumnNames().size() > 0) {
            doc.GetColumnName(0);
        }

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}