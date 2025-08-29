#!/bin/bash

# COMMIT_ID="7903db4"
REPO_URL="https://github.com/sqlite/sqlite.git"
TARGET_DIR="$COMMIT_ID"

git clone --depth 1 "$REPO_URL" code
if [ $? -ne 0 ]; then
    echo "Failed to clone repository. Exiting."
    exit 1
fi

if [ -n "$COMMIT_ID" ]; then
    cd code
    git checkout "$COMMIT_ID"
    if [ $? -ne 0 ]; then
        echo "Failed to checkout to commit $COMMIT_ID. Exiting."
        exit 1
    fi
    cd ..
fi

mkdir code/build
pushd code/build
../configure
make
popd

mkdir -p latest/code
cp code/README.md code/build/sqlite3.c code/build/sqlite3.h code/build/sqlite3ext.h ./Makefile latest/code
# Replace the header file
./replace_header.py latest/code/sqlite3.c

cp -r code/test latest/code
cp ./build.sh ./lib.toml latest
