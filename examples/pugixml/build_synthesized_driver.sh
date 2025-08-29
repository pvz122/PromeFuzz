#! /bin/bash

cd /promefuzz
clang++ /promefuzz/database/pugixml/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/pugixml/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/pugixml/latest/code/src database/pugixml/latest/bin_asan/lib/libpugixml.a -DPUGIXML_NO_XCEPTIONS
