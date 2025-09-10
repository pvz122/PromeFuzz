# Fuzz targets database

This directory contains several libraries that are configured to be tested using PromeFuzz.

## Dataset

We use 22 open-sourced libraries as our dataset, including 17 C libraries and 5 C++ libraries. They are:

| Library       | Version  | Language          |
| ------------- | -------- | ----------------- |
| c-ares        | 7978cf7  | C                 |
| curl          | 4c50998  | C                 |
| lcms          | 04ace9c  | C                 |
| libjpeg-turbo | 36ac5b84 | C                 |
| sqlite3       | 7903db4  | C                 |
| libaom        | 99fcd81  | C                 |
| libpcap       | 2559282  | C                 |
| libvpx        | 9514ab6  | C                 |
| zlib          | 5a82f71  | C                 |
| re2           | c84a140  | C++(or C binding) |
| libmagic      | dadc01f  | C                 |
| libpng        | 738f5e7  | C                 |
| ngiflib       | db19270  | C                 |
| ffjpeg        | caade6   | C                 |
| liblouis      | 3d95765  | C                 |
| libtiff       | fcd4c86  | C                 |
| cjson         | 12c4bf1  | C                 |
| pugixml       | 06318b0  | C++               |
| tinygltf      | a5e653e  | C++               |
| exiv2         | 04e1ea3  | C++               |
| loguru        | 4adaa18  | C++               |
| rapidcsv      | 083851d  | C++               |

## File Structure

Typically, each library is in a separate subdirectory, with `fetch.sh`, `install_deps.sh`, `build.sh` and `lib.toml` files inside, which should be executed in order:

1. `fetch.sh` downloads the library source code.
2. `install_deps.sh` installs the dependencies of the library.
3. `cd` into the library repository (defaultly to be `latest`), and run:
    - `build.sh normal` builds the library without any fuzzing instrumentation.
    - `build.sh asan` builds the library with AddressSanitizer.
    - `build.sh aflpp` builds the library with AFL++.
    - `build.sh gcov` builds the library with GCOV.
    - `build.sh cov` builds the library with LLVM-Cov.
    
    These built libraries are stored in the `build_xxx` and `bin_xxx` directories.
4. `lib.toml` is the configuration file for the PromeFuzz. After the library is built run PromeFuzz with `-F` option to process the library. For example, for preprocessing, run `./PromeFuzz.py -F database/xxx/latest/lib.toml preprocess`. All results are stored in the `database/xxx/latest/out` directory.

The `utils` directory contains some useful utilities for running the fuzz tests and parsing the results. Refer to the [README.md](utils/README.md) for more details.

## Reproducing Experiments

We also provide click-to-run scripts to easily reproduce experiments in [our paper](../paper/ccs25-full.pdf). These scripts are located in the `experiments` directory. Check [README.md](experiments/README.md) for more details.