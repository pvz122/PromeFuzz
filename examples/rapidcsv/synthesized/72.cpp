// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::GetCell at rapidcsv.h:1169:7 in rapidcsv.h
// rapidcsv::Document::SetCell at rapidcsv.h:1303:10 in rapidcsv.h
// rapidcsv::Converter::ToStr at rapidcsv.h:133:10 in rapidcsv.h
// rapidcsv::Converter::ToVal at rapidcsv.h:171:10 in rapidcsv.h
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

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *Data, size_t Size) {
    // Prepare input data
    std::string input(reinterpret_cast<const char*>(Data), Size);
    
    // Create dummy CSV file
    std::ofstream dummyFile("./dummy_file");
    if (!dummyFile.is_open()) return 0;
    
    // Write input data to dummy file
    dummyFile << input;
    dummyFile.close();

    // Initialize parameters
    rapidcsv::LabelParams labelParams{0};
    rapidcsv::SeparatorParams separatorParams{',', true};
    rapidcsv::ConverterParams converterParams{true, 0.0, 0};
    rapidcsv::LineReaderParams lineReaderParams{true, '#'};

    try {
        // Test Document::Load
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Test GetCell and SetCell with various types
        int testValue = 0;
        doc.GetCell<int>("Column1", "Row1", [&converterParams](const std::string& str, int& val) { 
            rapidcsv::Converter<int> converter(converterParams);
            converter.ToVal(str, val); 
        });
        
        // Modify the value and set it back
        testValue += 1;
        doc.SetCell<int>("Column1", "Row1", testValue);
        
        // Test Converter::ToVal
        rapidcsv::Converter<int> converter(converterParams);
        converter.ToVal("123", testValue);
        
        // Test Converter::ToStr
        std::string strValue;
        converter.ToStr(testValue, strValue);
        
    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}