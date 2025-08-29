#!/bin/bash

COMMIT_ID="$1"
REPO_URL="https://github.com/libming/libming.git"

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

mkdir latest
mv code latest
pushd latest/code && ./autogen.sh && popd || exit

cp ./build.sh ./lib.toml latest

echo "Repository successfully cloned and copied to '$TARGET_DIR' and latest."