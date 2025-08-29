// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::InsertRow at rapidcsv.h:1052:10 in rapidcsv.h
// rapidcsv::Document::SetCell at rapidcsv.h:1303:10 in rapidcsv.h
// rapidcsv::Document::SetCell at rapidcsv.h:1327:10 in rapidcsv.h
// rapidcsv::Document::Save at rapidcsv.h:569:10 in rapidcsv.h
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
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file
    const std::string filePath = "./dummy_file.csv";
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile.is_open()) {
        return 0;
    }

    // Write random data to the dummy file
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        // Setup parameters
        rapidcsv::LabelParams labelParams;
        labelParams.mColumnNameIdx = 0;

        rapidcsv::SeparatorParams separatorParams;
        separatorParams.mSeparator = ',';
        separatorParams.mTrim = true;

        rapidcsv::ConverterParams converterParams;
        converterParams.mHasDefaultConverter = true;
        converterParams.mDefaultFloat = 0.0;
        converterParams.mDefaultInteger = 0;

        rapidcsv::LineReaderParams lineReaderParams;
        lineReaderParams.mSkipCommentLines = true;
        lineReaderParams.mCommentPrefix = '#';

        // Load the document
        rapidcsv::Document doc(filePath, labelParams, separatorParams, converterParams, lineReaderParams);

        // Test SetCell with different types
        std::vector<std::string> rowData = {"Test1", "Test2", "Test3"};
        doc.InsertRow(0, rowData, "Row1");

        doc.SetCell(0, "Row1", "UpdatedCell1");
        doc.SetCell("Column1", "Row1", "UpdatedCell2");

        // Save the document
        doc.Save();
        doc.Save("./dummy_file_updated.csv");
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}