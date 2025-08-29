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
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_127(const uint8_t *Data, size_t Size) {
    // Prepare a dummy CSV file
    const std::string path = "./dummy_file.csv";
    std::ofstream ofs(path, std::ios::binary);
    if (ofs.is_open()) {
        ofs.write(reinterpret_cast<const char*>(Data), Size);
        ofs.close();
    }

    try {
        // Initialize parameters for loading the CSV
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

        // Create Document instance and load from file
        rapidcsv::Document doc(path, labelParams, separatorParams, converterParams, lineReaderParams);

        // Load from stream
        std::ifstream ifs(path);
        if (ifs.is_open()) {
            doc.Load(ifs, labelParams, separatorParams, converterParams, lineReaderParams);
            ifs.close();
        }

        // Save the document to a new file
        doc.Save("./output_file.csv");

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}