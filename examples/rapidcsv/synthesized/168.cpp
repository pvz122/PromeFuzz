// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Converter::ToStr at rapidcsv.h:133:10 in rapidcsv.h
// rapidcsv::Document::SetCell at rapidcsv.h:1345:10 in rapidcsv.h
// rapidcsv::Converter::ToVal at rapidcsv.h:171:10 in rapidcsv.h
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
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_168(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string input(reinterpret_cast<const char *>(Data), Size);
    std::ofstream dummyFile("./dummy_file");
    if (!dummyFile.is_open()) {
        return 0;
    }
    dummyFile << input;
    dummyFile.close();

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

    // Fuzzing Load method with file
    try {
        doc.Load("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Catch exceptions from Load
    }

    // Fuzzing Load method with stream
    std::istringstream stream(input);
    try {
        doc.Load(stream, labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Catch exceptions from Load
    }

    // Fuzzing SetCell method
    try {
        doc.SetCell<std::string>("Column1", 0, "Test");
    } catch (...) {
        // Catch exceptions from SetCell
    }

    // Fuzzing Converter ToVal and ToStr
    rapidcsv::Converter<int> converter(converterParams);
    int value;
    std::string strValue;
    try {
        converter.ToVal("123", value);
        converter.ToStr(value, strValue);
    } catch (...) {
        // Catch exceptions from ToVal and ToStr
    }

    return 0;
}