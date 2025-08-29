// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetCell at rapidcsv.h:1303:10 in rapidcsv.h
// rapidcsv::Document::Load at rapidcsv.h:526:10 in rapidcsv.h
// rapidcsv::Document::Load at rapidcsv.h:549:10 in rapidcsv.h
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
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    // Prepare dummy data for CSV
    std::string dummyData(reinterpret_cast<const char*>(Data), Size);
    std::ofstream outFile("./dummy_file");
    outFile << dummyData;
    outFile.close();

    // Initialize parameters
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

    try {
        // Load the document
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Fuzzing Save method
        doc.Save("./dummy_file_output");

        // Fuzzing Load method with stream
        std::ifstream inFile("./dummy_file");
        if (inFile.is_open()) {
            doc.Load(inFile, labelParams, separatorParams, converterParams, lineReaderParams);
            inFile.close();
        }

        // Fuzzing Load method with path
        doc.Load("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing SetCell method
        doc.SetCell<std::string>("Column1", "Row1", "TestValue");

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}