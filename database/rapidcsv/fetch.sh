#!/bin/bash

COMMIT_ID="$1"
REPO_URL="https://github.com/d99kris/rapidcsv.git"

git clone "$REPO_URL" code
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

# since this is a single-header library, we add a source file to include the header
echo '#include "rapidcsv.h"' > code/src/rapidcsv.cpp

mkdir latest
mv code latest

cp ./build.sh ./lib.toml latest
