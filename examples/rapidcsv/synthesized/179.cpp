// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetCell at rapidcsv.h:1327:10 in rapidcsv.h
// rapidcsv::Document::GetColumnName at rapidcsv.h:1361:17 in rapidcsv.h
// rapidcsv::Document::Load at rapidcsv.h:526:10 in rapidcsv.h
// rapidcsv::Document::Load at rapidcsv.h:549:10 in rapidcsv.h
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
#include <fstream>
#include <string>
#include <vector>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_179(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file with the input data
    std::ofstream outFile("./dummy_file");
    if (!outFile.is_open()) {
        return 0;
    }
    
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        rapidcsv::Document doc;

        // Prepare parameters for Load function
        rapidcsv::LabelParams labelParams;
        labelParams.mColumnNameIdx = 0; // Example index
        
        rapidcsv::SeparatorParams separatorParams;
        separatorParams.mSeparator = ','; // Example separator
        separatorParams.mTrim = true;

        rapidcsv::ConverterParams converterParams;
        converterParams.mHasDefaultConverter = true;
        converterParams.mDefaultFloat = 0.0;
        converterParams.mDefaultInteger = 0;

        rapidcsv::LineReaderParams lineReaderParams;
        lineReaderParams.mSkipCommentLines = true;
        lineReaderParams.mCommentPrefix = '#';

        // Invoke the Load function using the file path
        doc.Load("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);

        // Invoke the Load function using an input stream
        std::ifstream inFile("./dummy_file");
        if (inFile.is_open()) {
            doc.Load(inFile, labelParams, separatorParams, converterParams, lineReaderParams);
            inFile.close();
        }

        // Invoke GetColumnName with random index
        size_t randomIndex = rand() % 10; // Example random index
        std::string columnName = doc.GetColumnName(randomIndex);

        // Invoke SetCell with random values
        std::string randomRowName = "Row" + std::to_string(rand() % 10);
        doc.SetCell(randomIndex, randomRowName, "TestValue");
        
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}