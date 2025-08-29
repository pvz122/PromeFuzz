#! /bin/bash

cd /promefuzz
clang++ /promefuzz/database/rapidcsv/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/rapidcsv/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/rapidcsv/latest/code/src 
