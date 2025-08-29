// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::InsertRow at rapidcsv.h:1052:10 in rapidcsv.h
// rapidcsv::Document::SetCell at rapidcsv.h:1267:10 in rapidcsv.h
// rapidcsv::Document::Save at rapidcsv.h:582:10 in rapidcsv.h
// rapidcsv::Document::GetColumn at rapidcsv.h:626:20 in rapidcsv.h
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
#include <vector>
#include <cstdint>
#include <limits>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size) {
    // Prepare a dummy file to work with
    std::ofstream outFile("./dummy_file");
    if (!outFile) return 0;

    // Write the fuzz data to the dummy file
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        // Load the document from the dummy file
        rapidcsv::LabelParams labelParams(0, -1);
        rapidcsv::SeparatorParams separatorParams(',', false);
        rapidcsv::ConverterParams converterParams(false, std::numeric_limits<long double>::signaling_NaN(), 0);
        rapidcsv::LineReaderParams lineReaderParams(false, '#', false);
        
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);

        // Test Save function
        std::ostringstream outputStream;
        doc.Save(outputStream);

        // Test Load function with stream
        std::istringstream inputStream(outputStream.str());
        rapidcsv::Document docFromStream(inputStream, labelParams, separatorParams, converterParams, lineReaderParams);

        // Test GetColumn function
        std::vector<std::string> columnData = docFromStream.GetColumn<std::string>(0);

        // Test SetCell function
        docFromStream.SetCell<std::string>(0, 0, "Test");

        // Test InsertRow function
        docFromStream.InsertRow<std::string>(1, {"Inserted Row"});

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}