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

extern "C" int LLVMFuzzerTestOneInput_166(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file
    const std::string filePath = "./dummy_file";
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile) return 0;

    // Write random data to the dummy CSV file
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        rapidcsv::LabelParams labelParams;
        rapidcsv::SeparatorParams separatorParams;
        rapidcsv::ConverterParams converterParams;
        rapidcsv::LineReaderParams lineReaderParams;

        // Create a Document instance
        rapidcsv::Document doc(filePath, labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing GetRow
        size_t rowCount = doc.GetRowCount();
        if (rowCount > 0) {
            for (size_t i = 0; i < rowCount; ++i) {
                doc.GetRow<std::string>(i, [](const std::string& val, std::string& out) { out = val; });
            }
        }

        // Fuzzing RemoveRow
        if (rowCount > 0) {
            doc.RemoveRow(0); // Attempt to remove the first row
        }

        // Fuzzing SetRow
        if (rowCount > 0) {
            std::vector<std::string> newRow = {"test", "data"};
            doc.SetRow(0, newRow); // Attempt to set the first row
        }

        // Fuzzing SetRowName
        if (rowCount > 0) {
            doc.SetRowName(0, "NewRowName"); // Attempt to set a new row name
        }

        // Fuzzing InsertRow
        std::vector<std::string> insertRow = {"inserted", "row"};
        doc.InsertRow(0, insertRow, "InsertedRow"); // Attempt to insert a new row at the beginning

    } catch (...) {
        // Catch any exceptions thrown by rapidcsv
    }

    return 0;
}