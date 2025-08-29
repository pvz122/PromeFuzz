MODE=$1

JOBS=$(nproc)

if [[ $MODE == "angora" ]]; then
    export CC=$ANGORA/angora-clang
    export CXX=$ANGORA/angora-clang++
    # export ANGORA_TAINT_RULE_LIST=$PWD/zlib_abilist.txt
elif [[ $MODE == "normal" ]]; then
    export CC=clang
    export CXX=clang++
elif [[ $MODE == "asan" ]]; then
    export CC="clang -fsanitize=address,fuzzer-no-link -g "
    export CXX="clang++ -fsanitize=address,fuzzer-no-link -g "
    export CFLAGS="-g -O0"
    export CXXFLAGS="-g -O0"
    export CCFLAGS="-g -O0"
elif [[ $MODE == "gcov" ]]; then
    export CC="clang"
    export CXX="clang++"
    export CFLAGS="--coverage"
    export CXXFLAGS="--coverage"
    export CCFLAGS="--coverage"
    export LDFLAGS="--coverage"
elif [[ $MODE == "cov" ]]; then
    export CC="clang"
    export CXX="clang++"
    export CFLAGS="-fprofile-instr-generate -fcoverage-mapping"
    export CXXFLAGS="-fprofile-instr-generate -fcoverage-mapping"
    export CCFLAGS="-fprofile-instr-generate -fcoverage-mapping"
    export LDFLAGS="-fprofile-instr-generate -fcoverage-mapping"
elif [[ $MODE == "afl" ]]; then
    export CC=$AFL_PATH/afl-clang-fast
    export CXX=$AFL_PATH/afl-clang-fast++
elif [[ $MODE == "aflpp" ]]; then
    if [[ -z $AFLPP_PATH ]]; then
        if [[ -x "$(command -v afl-cc)" ]]; then
            AFLPP_PATH=$(dirname $(which afl-cc))
        else
            echo "[ERROR]: Please set AFLPP_PATH" 1>&2
            exit 1
        fi
    fi
    export CC=$AFLPP_PATH/afl-clang-fast
    export CXX=$AFLPP_PATH/afl-clang-fast++
    export AFL_LLVM_USE_TRACE_PC=1
    export AFL_USE_ASAN=1
elif [[ $MODE == "aflgo" ]]; then
    export CC="$AFLGO/afl-clang-fast"
    export CXX="$AFLGO/afl-clang-fast++"
    export SUBJECT=$PWD
    export TMP_DIR=$PWD/temp
    export ADDITIONAL="-targets=$TMP_DIR/BBtargets.txt -outdir=$TMP_DIR -flto -fuse-ld=gold -Wl,-plugin-opt=save-temps"
    rm -rf ./temp
    mkdir -p ./temp
elif [[ $MODE == "beacon" ]]; then
    export TMP_DIR=$PWD/temp
    export CC="gclang"
    export CXX="gclang++"
    export CFLAGS="-fPIC -g"
else
    echo "[ERROR]: Can not find Mode $MODE!" 1>&2
    exit 1
fi
