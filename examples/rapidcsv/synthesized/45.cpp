// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetColumnName at rapidcsv.h:1377:10 in rapidcsv.h
// rapidcsv::Document::GetColumn at rapidcsv.h:626:20 in rapidcsv.h
// rapidcsv::Document::GetColumn at rapidcsv.h:663:20 in rapidcsv.h
// rapidcsv::Document::SetColumn at rapidcsv.h:718:10 in rapidcsv.h
// rapidcsv::Document::RemoveColumn at rapidcsv.h:770:10 in rapidcsv.h
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
#include <rapidcsv.h>
#include <fstream>

static const std::string dummyFilePath = "./dummy_file";

static void writeDummyFile(const std::string& content) {
    std::ofstream dummyFile(dummyFilePath);
    if (dummyFile.is_open()) {
        dummyFile << content;
        dummyFile.close();
    }
}

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Prepare a dummy CSV file with random content
    std::string content(reinterpret_cast<const char*>(Data), Size);
    writeDummyFile(content);

    try {
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;

        // Create a Document from the dummy file
        rapidcsv::Document doc(dummyFilePath, labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing RemoveColumn
        size_t columnCount = doc.GetColumn<std::string>(0).size();
        if (columnCount > 0) {
            doc.RemoveColumn(columnCount - 1); // Try to remove the last column
        }

        // Fuzzing SetColumn
        std::vector<std::string> testColumn = {"test1", "test2", "test3"};
        if (columnCount > 0) {
            doc.SetColumn(columnCount - 1, testColumn); // Update last column with test data
        }

        // Fuzzing InsertColumn
        std::vector<std::string> newColumn = {"new1", "new2", "new3"};
        doc.InsertColumn(columnCount, newColumn, "NewColumn"); // Insert a new column at the end

        // Fuzzing GetColumn
        auto retrievedColumn = doc.GetColumn<std::string>(0); // Retrieve the first column

        // Fuzzing GetColumn with conversion function
        auto retrievedColumnWithConvFunc = doc.GetColumn<std::string>(0, [](const std::string& val, std::string& out) {
            out = val; // Identity conversion
        });

        // Fuzzing SetColumnName
        if (columnCount > 0) {
            doc.SetColumnName(columnCount - 1, "UpdatedColumnName"); // Update last column name
        }

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}