// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetCell at rapidcsv.h:1303:10 in rapidcsv.h
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
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_174(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string input(reinterpret_cast<const char*>(Data), Size);
    std::ofstream ofs("./dummy_file");
    ofs << input;
    ofs.close();

    rapidcsv::Document doc;

    // Prepare parameters
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

    // Fuzzing Load from file
    try {
        doc.Load("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Catch exceptions
    }

    // Fuzzing Load from stream
    std::istringstream stream(input);
    try {
        doc.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Catch exceptions
    }

    // Fuzzing SetCell
    try {
        doc.SetCell<std::string>("Column1", "Row1", "TestValue");
    } catch (...) {
        // Catch exceptions
    }

    return 0;
}