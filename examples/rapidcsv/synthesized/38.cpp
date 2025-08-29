// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetCell at rapidcsv.h:1303:10 in rapidcsv.h
// rapidcsv::Document::SetCell at rapidcsv.h:1327:10 in rapidcsv.h
// rapidcsv::Document::SetColumnName at rapidcsv.h:1377:10 in rapidcsv.h
// rapidcsv::Document::Save at rapidcsv.h:569:10 in rapidcsv.h
// rapidcsv::Document::SetColumn at rapidcsv.h:756:10 in rapidcsv.h
// rapidcsv::Document::RemoveColumn at rapidcsv.h:770:10 in rapidcsv.h
// rapidcsv::Document::RemoveColumn at rapidcsv.h:788:10 in rapidcsv.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    // Prepare a dummy file for saving
    const std::string dummyFilePath = "./dummy_file";
    std::ofstream dummyFile(dummyFilePath);
    if (!dummyFile.is_open()) return 0;

    // Write random data to the dummy file
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    // Initialize parameters
    rapidcsv::LabelParams labelParams;
    rapidcsv::SeparatorParams separatorParams;
    rapidcsv::ConverterParams converterParams;
    rapidcsv::LineReaderParams lineReaderParams;

    labelParams.mColumnNameIdx = 0; // Example index
    separatorParams.mSeparator = ','; // Default CSV separator
    converterParams.mHasDefaultConverter = true; // Allow default conversion
    converterParams.mDefaultFloat = 0.0;
    converterParams.mDefaultInteger = 0;
    lineReaderParams.mSkipCommentLines = true;
    lineReaderParams.mCommentPrefix = '#';

    try {
        // Create a Document instance
        std::ifstream inputFile(dummyFilePath);
        rapidcsv::Document doc(inputFile, labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing RemoveColumn method
        doc.RemoveColumn("column_name"); // Test with a sample column name

        // Fuzzing SetColumn method
        std::vector<int> columnData = {1, 2, 3, 4, 5};
        doc.SetColumn("column_name", columnData); // Test with a sample column name and data

        // Fuzzing Save method
        doc.Save(dummyFilePath); // Save back to dummy file

        // Fuzzing SetCell method
        doc.SetCell("column_name", "row_name", 10); // Using name overload
        doc.SetCell(0, "row_name", 20); // Using index overload

        // Fuzzing SetColumnName method
        doc.SetColumnName(0, "new_column_name"); // Change name of the first column

        // Fuzzing RemoveColumn method with index
        doc.RemoveColumn(0); // Remove the first column by index

    } catch (...) {
        // Catch all exceptions to avoid crashes
    }

    return 0;
}