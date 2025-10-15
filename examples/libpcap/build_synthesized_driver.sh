#! /bin/bash

cd /promefuzz
clang /promefuzz/database/libpcap/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/libpcap/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/libpcap/latest/code/pcap database/libpcap/latest/build_asan/libpcap.a -Idatabase/libpcap/latest/code -ldbus-1
