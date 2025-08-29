// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::SetColumnName at rapidcsv.h:1377:10 in rapidcsv.h
// rapidcsv::Document::GetColumnIdx at rapidcsv.h:608:9 in rapidcsv.h
// rapidcsv::Document::GetColumn at rapidcsv.h:702:20 in rapidcsv.h
// rapidcsv::Document::SetColumn at rapidcsv.h:756:10 in rapidcsv.h
// rapidcsv::Document::RemoveColumn at rapidcsv.h:788:10 in rapidcsv.h
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
#include <fstream>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    // Prepare dummy file
    std::ofstream ofs("./dummy_file");
    if (!ofs.is_open()) return 0;
    
    // Write random data to the file
    ofs.write(reinterpret_cast<const char*>(Data), Size);
    ofs.close();

    try {
        // Initialize LabelParams, SeparatorParams, ConverterParams, LineReaderParams
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

        // Create Document
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);

        // Fuzzing API functions
        std::string columnName = "TestColumn";
        std::vector<int> columnData = {1, 2, 3, 4, 5};

        // Test SetColumn
        doc.SetColumn(columnName, columnData);
        
        // Test GetColumnIdx
        int idx = doc.GetColumnIdx(columnName);
        
        // Test RemoveColumn
        doc.RemoveColumn(columnName);
        
        // Test InsertColumn
        doc.InsertColumn(0, columnData, columnName);
        
        // Test GetColumn
        auto retrievedData = doc.GetColumn<int>(columnName, [](const std::string& val, int& out) { out = std::stoi(val); });
        
        // Test SetColumnName
        doc.SetColumnName(0, "NewColumnName");

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}