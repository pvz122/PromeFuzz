# ClangAST-based processors

A set of processors based on Clang AST, implemented with ASTMatchers, including:

- **preprocessor**: process the target library and extract source code metadata.
- **cgprocessor**: process the library consumer code and extract call graph information.

## Build

The processors rely on the clang and llvm libraries. You should have them installed on your system.

```bash
sudo apt-get install clang llvm libclang-dev
```

Or you can download a specific version from the [LLVM Download Page](https://github.com/llvm/llvm-project/releases).

Then specify the environment variables `CLANG_INSTALL_DIR` to the clang installation directory, which can be found by executing `llvm-config --prefix`.

Finally build the processors using CMake:

```bash
mkdir build
cd build
CLANG_INSTALL_DIR=$(llvm-config --prefix) cmake ..
make
```

## Usage

The processors are used in the following way:

```bash
./preprocessor <source_file> -o <metadata_result> [-p <the_dir_of_compile_commands.json>] [-- <extra_clang_args>]
```

For example:

```bash
./build/bin/preprocessor processor/cxx/clang/example/example.cpp -o processor/cxx/clang/example/example.json
```

## Debug

For debugging, you can use the following command to dump the AST of a source file:

```bash
$ clang++ -Xclang -ast-dump -fsyntax-only -fno-color-diagnostics ./test.cc > test.ast
```