// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::AsciiValue::write at value.cpp:258:27 in value.hpp
// Exiv2::StringValueBase::write at value.cpp:205:32 in value.hpp
// Exiv2::DateValue::write at value.cpp:843:26 in value.hpp
// Exiv2::TimeValue::write at value.cpp:1020:26 in value.hpp
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::DataValue::write at value.cpp:137:26 in value.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/value.hpp>
#include <fstream>
#include <sstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_457(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        std::string dummy_file = "./dummy_file";
        std::ofstream out(dummy_file);
        out.write(reinterpret_cast<const char*>(Data), Size);
        out.close();

        std::stringstream ss;
        ss.write(reinterpret_cast<const char*>(Data), Size);

        // Test AsciiValue::write
        {
            std::string str(reinterpret_cast<const char*>(Data), Size);
            Exiv2::AsciiValue asciiVal(str);
            asciiVal.write(ss);
        }

        // Test StringValueBase::write
        {
            std::string str(reinterpret_cast<const char*>(Data), Size);
            Exiv2::StringValue stringVal(str);
            stringVal.write(ss);
        }

        // Test DateValue::write
        {
            int year = *Data % 10000;
            int month = (*Data + 1) % 12 + 1;
            int day = (*Data + 2) % 31 + 1;
            Exiv2::DateValue dateVal(year, month, day);
            dateVal.write(ss);
        }

        // Test TimeValue::write
        {
            int hour = *Data % 24;
            int minute = (*Data + 1) % 60;
            int second = (*Data + 2) % 60;
            int tzHour = (*Data + 3) % 24;
            int tzMinute = (*Data + 4) % 60;
            Exiv2::TimeValue timeVal(hour, minute, second, tzHour, tzMinute);
            timeVal.write(ss);
        }

        // Test DataValue::write
        {
            Exiv2::DataValue dataVal(Exiv2::undefined);
            if (Size > 0) {
                dataVal.read(Data, Size);
                dataVal.write(ss);
            }
        }

        // Test ValueType::write (using StringValue as concrete type)
        {
            std::string str(reinterpret_cast<const char*>(Data), Size);
            Exiv2::StringValue stringVal(str);
            Exiv2::Value* valType = &stringVal;
            valType->write(ss);
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}