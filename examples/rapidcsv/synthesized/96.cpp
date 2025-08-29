// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
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

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size) {
    // Prepare a dummy file
    std::string dummyFilePath = "./dummy_file";
    std::ofstream dummyFile(dummyFilePath, std::ios::binary);
    if (dummyFile.is_open()) {
        dummyFile.write(reinterpret_cast<const char*>(Data), Size);
        dummyFile.close();
    }

    try {
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

        // Load from file
        rapidcsv::Document doc(dummyFilePath, labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Save to file
        doc.Save(dummyFilePath);

        // Load from stream
        std::ifstream stream(dummyFilePath);
        if (stream.is_open()) {
            doc.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);
            stream.close();
        }
    } catch (...) {
        // Catch exceptions to avoid crashes
    }

    return 0;
}