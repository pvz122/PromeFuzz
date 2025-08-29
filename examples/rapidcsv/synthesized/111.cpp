// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::no_converter::what at rapidcsv.h:103:17 in rapidcsv.h
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
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_111(const uint8_t *Data, size_t Size) {
    // Prepare dummy CSV file
    std::ofstream file("./dummy_file");
    if (!file.is_open()) return 0;

    // Create a string from the input data
    std::string input(reinterpret_cast<const char*>(Data), Size);
    file << input; // Write data to the dummy file
    file.close();

    // Prepare parameters for Load function
    rapidcsv::LabelParams labelParams(0, -1);
    rapidcsv::SeparatorParams separatorParams(',', false);
    rapidcsv::ConverterParams converterParams(false, 0.0, 0);
    rapidcsv::LineReaderParams lineReaderParams(false, '#', false);

    // Test Load from file overload
    try {
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
    } catch (...) {
        // Catch exceptions silently
    }

    // Test Load from stream overload
    try {
        std::ifstream stream("./dummy_file");
        if (stream.is_open()) {
            rapidcsv::Document doc(stream, labelParams, separatorParams, converterParams, lineReaderParams);
        }
    } catch (...) {
        // Catch exceptions silently
    }

    // Test Converter::ToStr and Converter::ToVal
    try {
        rapidcsv::Converter<int> converter(converterParams);
        std::string str;
        int value = 42;
        converter.ToStr(value, str);

        std::string inputStr = "123";
        converter.ToVal(inputStr, value);
    } catch (...) {
        // Catch exceptions silently
    }

    // Test no_converter::what
    try {
        rapidcsv::no_converter nc;
        const char* msg = nc.what();
    } catch (...) {
        // Catch exceptions silently
    }

    return 0;
}