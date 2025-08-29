#!/bin/bash

COMMIT_ID="$1"
REPO_URL="https://github.com/file/file.git"

echo "Cloning repository..."
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

pushd code
autoreconf -fi
popd

mkdir latest
mv code latest

cp ./build.sh ./lib.toml latest

# make seeds from test files
rm -rf in
mkdir in
cp latest/code/tests/*.testfile in/

echo "Repository successfully cloned and copied to latest."
